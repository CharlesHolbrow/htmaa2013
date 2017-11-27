#include <avr/io.h>

void init_input(){
  PORTA |= (1 << 2); // enable aux    pull up resistor (PA2)
  PORTA |= (1 << 3); // enable button pull up resistor (PA3)
}


