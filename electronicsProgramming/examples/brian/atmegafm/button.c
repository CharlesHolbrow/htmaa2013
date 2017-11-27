#include <avr/io.h>

#include "button.h"

static uint8_t button_event;
static uint8_t button_last;

void button_init(void) {
    button_event = 0;
    button_last = 0;

    PORTC |= (1<<PC0);
}

uint8_t button_pressed(void) {
    uint8_t button_state = (! (PINC & (1<<PC0)));
    if(button_state && !button_last) {
        button_last = button_state;
        return 1;
    }
    button_last = button_state;
    return 0;
}

