#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "input.h"
#include "output.h"
#include "serial.h"


static unsigned volatile int water;


ISR(TIM1_OVF_vect) {
  static volatile int chr;
  chr = (char) (water / 512) ;
  led_level(chr);
  ez_put_char(chr);
  water = 0;
}

int main()
{  
  static char chr;
  
  init_input();
  init_pwm();
  init_serial();
  init_big_counter();

  led_level(0);
  sei();

  while(1) 
  {
    if (water()) ++water;
  }

}

