#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "mixer.h"
#include "audio.h"
#include "config.h"
#include "sinetable.h"
#include "pitch.h"

// Variable to hold the next sample that will be output to the speaker
static volatile uint8_t next_sample;

// Flag indicating whether the next sample has been computed.
static volatile uint8_t mixer_ready;

// Memory to hold the status of all of the mixer channels
mixer_channel_t channels[N_CHANNELS];

void mixer_init(void) {
    uint8_t i;

    // Initialize global state
    next_sample = 0;
    mixer_ready = 1;

    // Initialize channels
    for(i=0; i<N_CHANNELS; i++) {
        channels[i].volume = 80;
        channels[i].carrier_inc = 0;
        channels[i].modulator_inc = 0;
        channels[i].carrier_pos = 0;
        channels[i].modulator_pos = 0;
        channels[i].envelope_pos = 0;
        channels[i].instrument = instruments[1];
    }

    // Set up Timer 0 to schedule the mixer.
    TCCR0A = (1<<WGM01);
    TCCR0B = (1<<CS01) | (1<<CS00);
    OCR0A = 25;
    TIMSK0 |= (1<<OCIE0A);
}

void mixer_start_note(uint8_t channel, uint8_t note) {
    mixer_channel_t *chan = &channels[channel];
    instrument_t const *instr = chan->instrument;
    chan->carrier_inc = note_to_increment(note);
    chan->modulator_inc = chan->carrier_inc * instr->mod_ratio_numerator / 
        instr->mod_ratio_denominator;
    chan->envelope_pos = 0;
    chan->released = 0;
}

void mixer_end_note(uint8_t channel) {
    channels[channel].released = 1;
}

void mixer_set_instrument(uint8_t channel, uint8_t instr_index) {
    channels[channel].instrument = instruments[instr_index];
}

void mixer_set_volume(uint8_t channel, uint8_t volume) {
    channels[channel].volume = volume;
}

// This function is the meat of the program.  The next sample to output on the
// speaker is computed here.
void mixer_task(void) {
    uint8_t i;
    uint8_t cpos, mpos;
    uint16_t s;
    uint8_t amplitude;
    int16_t modulation;
    uint16_t mixed_sample = 0;
    mixer_channel_t *chan;
    instrument_t const *instr;
    envelope_t const *env;

    if(mixer_ready) return;
    
    for(i=0; i<N_CHANNELS; i++) {
        chan = &channels[i];

        // Don't waste time on silent channels
        if(chan->carrier_inc == 0) continue;

        instr = chan->instrument;
        env = envelopes[instr->envelope_index];

        // Kernel of the synthesis starts
        chan->modulator_pos += chan->modulator_inc;
        mpos = (chan->modulator_pos >> POS_FRAC_BITS) & SINETABLE_MASK;
        modulation = (pgm_read_byte(&sinetable[mpos]) << 4) >> instr->modulation_index;

        // Increment wavetable positions
        chan->carrier_pos += chan->carrier_inc;
        chan->envelope_pos += instr->env_increment;

        // Don't run off the end of the envelope
        if(chan->envelope_pos > (env->hold << 7) && !chan->released) {
            chan->envelope_pos = (env->hold << 7);
        } else if(chan->envelope_pos > 0x7FFF) {
            chan->envelope_pos = 0x7FFF;
            chan->carrier_inc = 0;
        }

        // Compute modulated position, grab the sample, apply amplitude
        // envelope and channel volume
        cpos = ((chan->carrier_pos + modulation) >> POS_FRAC_BITS) & SINETABLE_MASK;
        amplitude = (chan->volume * pgm_read_byte(
                &env->table[chan->envelope_pos >> 7])) >> 8;
        s = (uint16_t)pgm_read_byte(&sinetable[cpos]) * amplitude;

        // Mix in the sample for this channel
        mixed_sample += (s  >> 8);
    }
    
    next_sample = (mixed_sample & 0xFF);
    mixer_ready = 1;
}



// Interrupt triggered by the sample clock.  Here, we output the next sample, and
// set a flag 
ISR(TIMER0_COMPA_vect) {
    audio_output(next_sample);
    mixer_ready = 0;
}

