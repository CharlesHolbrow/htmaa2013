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

  // Enable PWM via Timer/Clock Control Register
  TCCR0A |= (1 << COM0B1); // OC0B aka PA7
  TCCR0A |= (1 << COM0A1); // OC0A aka PB2

  // Clock  divider - Data sheet Page 82
  TCCR0B = (0<<CS02) | (1<<CS01) | (0<<CS00); // does not effect _delay_ms()

  led_level(127);
  out_duty(127);
}

void init_big_counter()
{
  // start Timer Counter 1 (P. 109)
  TCCR1B |= (1 << CS10);

  // start with divider
  // TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);

  // Timer 1 Overflow interrupt (P 111) - ISR(TIM1_OVF_vect)
  TIMSK1 |= (1 << TOIE1);
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

  // Timer Counter 1 Output Compare A Match Interrupt Enable (P. 111)
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