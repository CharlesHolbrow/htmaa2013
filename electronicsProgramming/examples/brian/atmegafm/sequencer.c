#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "sequencer.h"
#include "mixer.h"
#include "led.h"
#include "config.h"
#include "opcodes.h"

static uint8_t seq_counts;
static uint8_t seq_playing;
static uint8_t seq_div;
static uint8_t seq_div_per_beat;
static uint8_t const *seq_ptr;
static uint8_t active_channels;
static volatile uint8_t seq_speed;
static volatile uint8_t seq_flag;

void sequencer_init(void) {
    seq_counts = 0;
    seq_flag = 0;
    seq_speed = 10;
    seq_div = 0;
    seq_div_per_beat = 4;
    seq_playing = 0;
    active_channels = 4;

    TCCR2A = (1<<WGM21);
    TCCR2B = (1<<CS22) | (1<<CS21) | (1<<CS20);
    OCR2A = 196;
    TIMSK2 |= (1<<OCIE2A);
}

void sequencer_task(void) {
    uint8_t i;
    uint8_t op, arg1, arg2;
    uint8_t play_notes;
    if(!seq_flag || !seq_playing) return;
    seq_flag = 0;

    play_notes = 1;
   
cmd_start:
    arg1 = pgm_read_byte(&seq_ptr[0]);
    op = arg1 >> 4;
    arg1 &= 0x0F;
    if(op >= 0x8) {
        switch(op){ 
            case OP_SONGEND:
                seq_playing = 0;
                led_off();
                return;
            case OP_REST:
                play_notes = 0;
                seq_ptr++;
                break;
            case OP_SET_N_CHAN:
                active_channels = arg1;
                seq_ptr++;
                goto cmd_start;
            case OP_SET_INSTRUMENT:
                arg2 = pgm_read_byte(&seq_ptr[1]);
                mixer_set_instrument(arg1, arg2);
                seq_ptr += 2;
                goto cmd_start;
            case OP_SET_VOLUME:
                arg2 = pgm_read_byte(&seq_ptr[1]);
                mixer_set_volume(arg1, arg2);
                seq_ptr += 2;
                goto cmd_start;
            case OP_SET_SPEED:
                arg2 = pgm_read_byte(&seq_ptr[1]);
                sequencer_set_speed(arg2);
                seq_ptr += 2;
                goto cmd_start;
        }
    }

    if(play_notes) {
        for(i=0; i<active_channels; i++) {
            uint8_t note = pgm_read_byte(&seq_ptr[i]);
            if(note > 1 && note < 128) {
                mixer_start_note(i, note);
            } else if(note == 1) {
                mixer_end_note(i);
            }
        }
        seq_ptr+=active_channels;
    }


    seq_div++;
    if(seq_div == seq_div_per_beat) {
        seq_div = 0;
        led_on();
    } else {
        led_off();
    }
}

void sequencer_load(const uint8_t *address) {
    seq_ptr = address;
    seq_playing = 1;
}

void sequencer_set_speed(uint8_t speed) {
    seq_speed = speed;
}

ISR(TIMER2_COMPA_vect) {
    seq_counts++;
    if(seq_counts == seq_speed) {
        seq_counts = 0;
        seq_flag = 1;
    }
}


