#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "output.h"

ISR(TIM1_COMPA_vect){
  static volatile unsigned char duty = 0; // do these need to be volatile?
  static volatile unsigned char state = 0;

  out_duty(duty++);

  if (duty > 127) duty = 0;
  // duty++;

  // if (state++ % 16 == 0)
  //   led_level(255);
  // else
  //   led_level(0);
}


int main()
{
  static unsigned char level = 0;
  float ms = 0;

  // pwm
  init_pwm();
  audio_on();

  // audio stuff
  init_audio_clock();

  // globally enable interrupts
  sei();

  while(1){
    _delay_ms(1000);
    audio_off();
    _delay_ms(1000);
    audio_on();
  }

} // main

