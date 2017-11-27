#define F_CPU 2500000UL
#include <util/delay.h>
#include <avr/io.h>

#include "master.h"
#include "bit_ops.h"
#include "led.h"

#define clock_high() bit_set(PORTA, BIT(4))
#define clock_low() bit_clear(PORTA, BIT(4))

#define mosi_high() bit_set(PORTA, BIT(6))
#define mosi_low() bit_clear(PORTA, BIT(6))

void init_master()
{
  bit_set(DDRA, BIT(6)); // set PA6 as output
  bit_set(DDRA, BIT(4)); // set clock as output
  clock_high();
}

void talk_to(unsigned char node, unsigned char value)
{
  unsigned char i;
  unsigned char state;
  unsigned int data;
  unsigned int one = 1;

  // 16 bits, node is first, followed by value
  data = value;
  data = data << 8;
  data += node;

  mosi_low();
  clock_low();

  // send each bit from char
  for (i = 0; i < 16; i++){
    // state = (one << i) & data;
    if ((one << i) & data) {
      mosi_high();
      led_on();
    }
    else {
      mosi_low();
      led_off();
    }
    _delay_ms(BIT_MS);
  }
  
  mosi_low();
  led_off();
  clock_high();
}