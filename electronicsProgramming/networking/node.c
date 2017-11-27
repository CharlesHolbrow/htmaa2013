#include <avr/io.h>

#define F_CPU 2500000UL
#include <util/delay.h>

#include "bit_ops.h"
#include "led.h"
#include "master.h"
#include "slave.h"

#define NODE 2

int main()
{ 
  
  // Button  PA3 (pin 10)
  bit_set(PORTA,BIT(3)); // Enable button pull up resistor

  init_led();

  if (NODE) {
    init_slave();
    listen(NODE);
  }

  else   {
    // indicate we are in master mode
    blink(1); 
    init_master();

    while(1) {
      talk_to(1, 2);
      _delay_ms(5000);
      talk_to(2, 3);
      _delay_ms(5000);
    }
  }

}
