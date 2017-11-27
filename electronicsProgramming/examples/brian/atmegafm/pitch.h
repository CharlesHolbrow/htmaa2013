#ifndef __pitch_h_
#define __pitch_h_

#include <stdint.h>
#include "config.h"
#include "sinetable.h"

#define FREQ_TO_INCREMENT(x) (((x * 64) * SINETABLE_SIZE ) / SAMPLE_RATE)
//#define FREQ_TO_INCREMENT(x)

uint16_t note_to_increment(uint8_t note);

#endif // __pitch_h_

