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

  // Turn button pull up resistor on by setting PA2 and PA3 
  bit_set(PORTA,BIT(3));
  bit_set(PORTA,BIT(2));

  // Enable output on the LED pin 
  bit_set(DDRA,BIT(7));
  
  // Enable output on header pin 2 / PB2 / Pin 5
  bit_set(DDRB,1 << 2);

  blink();

  // Clock  divider - Data sheet Page 82
  TCCR0B = (1<<CS02) | (0<<CS01) | (1<<CS00); // does not effect _delay_ms()

  // Fast PWM
  TCCR0A |= (1 << WGM01); // 1
  TCCR0A |= (1 << WGM00); // 0

  // Timer Clock Control. Set COM0B0 for Inverting
  TCCR0A |= (1 << COM0B1) | (0 << COM0B0);
  TCCR0A |= (1 << COM0A1) | (0 << COM0A0);

  // Compared with counter at all times
  // Output Compare Register 0A can generate pwm on pin 5
  OCR0A = 50;
  _delay_ms(500);
  OCR0A = 200;
  _delay_ms(5000);
  OCR0A = 127;

  _delay_ms(1000);

  // Output Compare Register 0B can generate pwm on pin 6
  OCR0B = 1;
  _delay_ms(1000);
  OCR0B = 255;
  _delay_ms(1000);
  OCR0B = 127;
  _delay_ms(1000);
  OCR0B = 255;

  for(;;);
}


