#include <avr/io.h>
#include <avr/interrupt.h>

#include "output.h"

void init_pwm()
{
  // Enable output on the LED PA7/PIN6
  DDRA |= (1 << 7);

  // Configure OC0A/PB2/Pin5 as output
  DDRB |= (1 << 2);

  // Enable Fast PWM via Wave Generation Mode bits (P.81)
  TCCR0A |= (1 << WGM01) | (1 << WGM00); 

  // Enable Phase Correct PWM
  //TCCR0A |= (0 << WGM02) | (0 << WGM01) | (1 <<WGM00);

  // Timer/Clock Control Register
  // Enable PWM on both OC0A and OC0B pins
  TCCR0A |= (1 << COM0B1);
  TCCR0A |= (1 << COM0A1);

  // Clock  divider - Data sheet Page 82
  TCCR0B = (0<<CS02) | (1<<CS01) | (0<<CS00); // does not effect _delay_ms()

  led_level(127);
  out_duty(127);
}

// ------------------------------------------------------------
// we use a 16 bit counter
// Call init_audio_clock before calling sei().
void init_audio_clock()
{
  // start Timer Counter 1 (P. 109)
  TCCR1B |= (1 << CS10);

  // Wave Generate Mode (P. 108)
  TCCR1B |= (1 << WGM12);

  OCR1A = 1250; // 16kHz sample rate
  // OCR1A = 1000; // 20kHz sample rate

  // Timer Counter 1 Output Compare A Match Interrupt Enable
  TIMSK1 |= (1 << OCIE1A); // ISR(TIM1_COMPA_vect)
}


// Normal port operation, OC0A disconnected
void audio_off()
{
  TCCR0A &= ~(1 << COM0A1);
}
// Clear OC0A on Compare Match, Set OC0A at BOTTOM (non-inverting mode)
void audio_on()
{
  TCCR0A |=(1 << COM0A1);
}