#include <avr/io.h>

#define F_CPU 2500000UL
#include <util/delay.h>

#define bit_get(p,m) ((p) & (m)) 
#define bit_set(p,m) ((p) |= (m)) 
#define bit_clear(p,m) ((p) &= ~(m)) 
#define BIT(x) (0x01 << (x)) 

void blink(int seconds)
{
  int i;
  for (i = 0; i < seconds; i++)
  {
    _delay_ms(500);
    bit_set(PORTA,BIT(7));

    _delay_ms(500);
    bit_clear(PORTA,BIT(7));

  }
}

int main()
{
  // Button  PA3 (pin 10)
  // LED     PA7 (pin 6)
  bit_set(PORTA,BIT(3));  // Turn button pull up resistor on by setting PA3(input) high
  bit_set(DDRA,BIT(7));   // Enable output on the LED pin (PB2)

  blink(5); // blink for 5 seconds

  while (1)
  {
    if(bit_get(PINA,BIT(3)))  // Button is up, turn on
      bit_set(PORTA,BIT(7));
    else                      // Button is down, turn off
      bit_clear(PORTA,BIT(7));
  }
}


