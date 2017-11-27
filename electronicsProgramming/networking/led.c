#define F_CPU 2500000UL
#include <util/delay.h>
#include <avr/io.h>

#include "led.h"
#include "bit_ops.h"

void blink(int seconds)
{
  int i;
  for (i = 0; i < seconds; i++)
  {
    _delay_ms(500);
    led_on();
    _delay_ms(500);
    led_off();
  }
}

void init_led()
{
  bit_set(DDRA,BIT(7));   // Config LED pin (PB2) as output
  led_off();
}