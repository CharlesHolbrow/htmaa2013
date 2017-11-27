#ifndef __sequencer_h_
#define __sequencer_h_

#include <stdint.h>

void sequencer_init(void);
void sequencer_task(void);
void sequencer_load(const uint8_t *address);
void sequencer_set_speed(uint8_t speed);

#endif // __sequencer_h_

