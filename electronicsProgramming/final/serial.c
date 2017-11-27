//
//
// hello.ftdi.44.echo.c
//
// 115200 baud FTDI character echo, with flash string
//
// set lfuse to 0x7E for 20 MHz xtal
//
// Neil Gershenfeld
// 12/8/10
//
// (c) Massachusetts Institute of Technology 2010
// Permission granted for experimental and personal use;
// license for commercial sale available from MIT.
//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "helpers.h"
#include "serial.h"

#define serial_pins PINA
#define serial_port PORTA
#define serial_pin_in (1 << PA0)
#define serial_pin_out (1 << PA1)


void init_serial(){
  PORTA |= serial_pin_out;
  DDRA |= serial_pin_out;
}

void ez_put_char(char chr){
   put_char(&serial_port, serial_pin_out, chr);
   // get_char(&serial_pins, serial_pin_in, &chr);
   // put_char(&serial_port, serial_pin_out, chr);
}

void get_char(volatile unsigned char *pins, unsigned char pin, char *rxbyte) {

   // read character into rxbyte on pins pin
   //    assumes line driver (inverts bits)
   *rxbyte = 0;
   while (pin_test(*pins,pin))
      // wait for start bit
      ;
   cli();

   // delay to middle of first data bit
   half_bit_delay();
   bit_delay();

   // unrolled loop to read data bits
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 0);
   else
      *rxbyte |= (0 << 0);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 1);
   else
      *rxbyte |= (0 << 1);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 2);
   else
      *rxbyte |= (0 << 2);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 3);
   else
      *rxbyte |= (0 << 3);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 4);
   else
      *rxbyte |= (0 << 4);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 5);
   else
      *rxbyte |= (0 << 5);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 6);
   else
      *rxbyte |= (0 << 6);
   bit_delay();
   if pin_test(*pins,pin)
      *rxbyte |= (1 << 7);
   else
      *rxbyte |= (0 << 7);

   // wait for stop bit
   bit_delay();
   half_bit_delay();
   sei();
   }

void put_char(volatile unsigned char *port, unsigned char pin, char txchar) {

   // send character in txchar on port pin
   //    assumes line driver (inverts bits)

   // start bit
   cli();
   clear(*port,pin);
   bit_delay();

   // unrolled loop to write data bits
   if bit_test(txchar,0)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,1)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,2)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,3)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,4)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,5)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,6)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();
   if bit_test(txchar,7)
      set(*port,pin);
   else
      clear(*port,pin);
   bit_delay();

   // stop bit
   set(*port,pin);
   bit_delay();

   // char delay
   bit_delay();
   sei();
   }

void put_flash_string(volatile unsigned char *port, unsigned char pin, PGM_P str) {

   // print a null-terminated string from flash
   static char chr;
   static int index;
   index = 0;
   do {
      chr = pgm_read_byte(&(str[index]));
      put_char(port, pin, chr);
      ++index;
      } while (chr != 0);
   }

void put_ram_string(volatile unsigned char *port, unsigned char pin, char *str) {

   // print a null-terminated string from SRAM
   static int index;
   index = 0;
   do {
      put_char(port, pin, str[index]);
      ++index;
      } while (str[index] != 0);
   }
