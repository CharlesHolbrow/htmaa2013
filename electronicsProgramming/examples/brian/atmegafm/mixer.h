#ifndef __mixer_h_
#define __mixer_h_

#include "envelope.h"
#include "instrument.h"

typedef struct {
    uint16_t carrier_inc;
    uint16_t modulator_inc;
    uint16_t carrier_pos;
    uint16_t modulator_pos;
    uint16_t envelope_pos;
    uint8_t volume;
    uint8_t released;
    instrument_t const *instrument;
} mixer_channel_t;

extern mixer_channel_t channels[];

void mixer_init(void);
void mixer_task(void);
void mixer_start_note(uint8_t channel, uint8_t note);
void mixer_end_note(uint8_t channel);
void mixer_set_instrument(uint8_t channel, uint8_t instr_index);
void mixer_set_volume(uint8_t channel, uint8_t volume);

#endif // __mixer_h_

