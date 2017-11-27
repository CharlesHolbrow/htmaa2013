#ifndef __envelope_h_
#define __envelope_h_

#include <avr/pgmspace.h>
#include <stdint.h>

#define ENVELOPE_LENGTH 256

typedef struct {
    const uint8_t *table;
    uint16_t increment;
    uint8_t hold;
} envelope_t;

extern const envelope_t const *envelopes[];

#endif // __envelope_h_

