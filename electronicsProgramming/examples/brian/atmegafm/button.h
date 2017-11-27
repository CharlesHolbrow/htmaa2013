#ifndef __button_h_
#define __button_h_

#include <stdint.h>

void button_init(void);
void button_task(void);
uint8_t button_pressed(void);

#endif // __button_h_

