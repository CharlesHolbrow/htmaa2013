#define F_CPU 2500000UL
#include <util/delay.h>
#include <avr/io.h>

#include "bit_ops.h"
#include "led.h"

#define MOSI (bit_get(PINA, BIT(6)))

void init_slave()
{
  bit_clear(DDRA, BIT(4)); // config clock as input
  bit_set(PORTA, BIT(6)); // enable pull up resistor MOSI
  bit_set(PORTA, BIT(4)); // enable pull up resistor on clock input
}

void listen(unsigned char address){

  unsigned char node; // message destination 
  unsigned char value; // message contents
  unsigned char i;
  unsigned int data;
  unsigned int one = 1;


  blink(2);

  while(1){
    if (!bit_get(PINA, BIT(4)))
    {
      // the clock is low. expect two chars 
      _delay_ms(HALF_BIT_MS);
      data = 0;

      // receive each bit
      for (i = 0; i < 16; i++){
        if (MOSI){
          led_on();
          bit_set(data, (one << i));
        } else {
          led_off();
        }
        _delay_ms(BIT_MS);
      }

      node = data & 0xff;
      value = data >> 8;
      if (node == address) blink(value);
      led_off();
    }
  }

}