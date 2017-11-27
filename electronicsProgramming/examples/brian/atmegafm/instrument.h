#ifndef __instrument_h_
#define __instrument_h_

#include <stdint.h>

#include "envelope.h"

typedef struct {
    uint8_t envelope_index;
    uint16_t env_increment;
    uint8_t modulation_index;
    uint8_t mod_ratio_numerator;
    uint8_t mod_ratio_denominator;
    uint8_t attenuation;
} instrument_t;

extern const instrument_t const *instruments[];

#endif // __instrument_h_

