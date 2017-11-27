#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "helpers.h"
#include "serial.h"

#define serial_pins PINA
#define serial_port PORTA
#define serial_pin_in (1 << PA0)
#define serial_pin_out (1 << PA1)

int main(void) 
{
    static char chr;

    // initialize serial output pins
    PORTA |= serial_pin_out;
    DDRA |= serial_pin_out;

    // main loop
    while (1) {
        get_char(&serial_pins, serial_pin_in, &chr);

        _delay_ms(1000);
        put_char(&serial_port, serial_pin_out, chr);
        put_char(&serial_port, serial_pin_out, 'q');
        put_char(&serial_port, serial_pin_out, 10); // new line
        // _delay_ms(1000);
        // put_ram_string(&serial_port, serial_pin_out, "a curse upon you!");
    }
}
