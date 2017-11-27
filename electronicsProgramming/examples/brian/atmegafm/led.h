#ifndef __led_h_
#define __led_h_

#include <avr/io.h>

#define led_on() PORTC &= ~(1<<PC5)
#define led_off() PORTC |= (1<<PC5)

void led_init(void);

#endif // __led_h_

