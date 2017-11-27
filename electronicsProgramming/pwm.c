#include <avr/io.h>

#define F_CPU 2500000UL
#include <util/delay.h>

#define bit_get(p,m) ((p) & (m)) 
#define bit_set(p,m) ((p) |= (m)) 
#define bit_clear(p,m) ((p) &= ~(m)) 
#define BIT(x) (0x01 << (x)) 

void blink()
{
  bit_clear(PORTA,BIT(7));  // off
  _delay_ms(200);
  bit_set(PORTA,BIT(7));    // on
  _delay_ms(200);
  bit_clear(PORTA,BIT(7));  // off
  _delay_ms(200);
  bit_set(PORTA,BIT(7));    // on
  _delay_ms(200);
}


int main()
{
  // Button  PA3 (pin 10)
  // LED     PA7 (pin 6)
  bit_set(PORTA,BIT(3));  // Turn button pull up resistor on by setting PA3(input) high
  bit_set(DDRA,BIT(7));   // Enable output on the LED pin 

  blink();

  // Clock  divider - Data sheet Page 82
  TCCR0B = (0<<CS02) | (1<<CS01) | (1<<CS00); // does not effect _delay_ms()

  // Fast PWM
  TCCR0A |= (1 << WGM01); // 1
  TCCR0A |= (1 << WGM00); // 0

  // Timer Clock Control. Set COM0B0 for Inverting
  TCCR0A |= (1 << COM0B1) | (0 << COM0B0); // 5

  // Compared with timer at all times
  OCR0B = 1;
  _delay_ms(1000);
  OCR0B = 255;
  _delay_ms(1000);
  OCR0B = 127;

  for(;;);
}


