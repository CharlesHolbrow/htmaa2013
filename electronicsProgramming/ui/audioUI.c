#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "output.h"
#include "serial.h"

#define serial_pins PINA
#define serial_port PORTA
#define serial_pin_in (1 << PA0)
#define serial_pin_out (1 << PA1)

ISR(TIM1_COMPA_vect){
  static volatile unsigned char duty = 0; // do these need to be volatile?
  out_duty(duty++);
}


int main()
{

  static char chr;

  // initialize serial output pins
  PORTA |= serial_pin_out;
  DDRA |= serial_pin_out;

  // pwm
  init_pwm();
  audio_off();

  // audio stuff
  init_audio_clock();

  // globally enable interrupts
  sei();

  get_char(&serial_pins, serial_pin_in, &chr);
  audio_on();
    
  while(1){
    get_char(&serial_pins, serial_pin_in, &chr);
    put_char(&serial_port, serial_pin_out, chr);
    led_level(chr);
    OCR1A = 1250 - (9 * chr);
  }

} // main

