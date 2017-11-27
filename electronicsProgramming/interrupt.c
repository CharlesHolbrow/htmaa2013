#include <avr/io.h>

#define F_CPU 2500000UL
#include <util/delay.h>
#include <avr/interrupt.h>

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

// For some reason PCINT0_vect AND PCINT3_vect both work???
ISR(PCINT0_vect){ 
  blink();
}

int main()
{
  // Button  PA3 (pin 10)
  // LED     PA7 (pin 6)
  bit_set(PORTA,BIT(3));  // Turn button pull up resistor on by setting PA3(input) high
  bit_set(DDRA,BIT(7));   // Enable output on the LED pin 

  // GIMSK - General Interrupt Mask Register
  // When the PCIE0 bit is set (one) and the I-bit in the 
  // Status Register (SREG) is set (one), pin change interrupt
  //  0 is enabled. Any change on any enabled PCINT7..0 pin 
  // will cause an interrupt. The corresponding interrupt of 
  // Pin Change Interrupt Request is executed from the PCI0 
  // Interrupt Vector. 
  // PCINT7..0 pins are enabled individually by the PCMSK0 Register.
  GIMSK |= (1 << PCIE0);

  // PCMSK0 - Pin Change Mask Register 0 - one bit for each pin on PortA
  PCMSK0 |= (1 << PCINT3); // enable interrupt for change on pin3

  // globally enable interrupts
  sei(); 

  blink();

  while (1)
  {
  }
}


