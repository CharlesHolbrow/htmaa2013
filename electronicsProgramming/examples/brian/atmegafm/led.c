#include "led.h"

void led_init(void) {
    DDRC |= (1<<PC5);
    led_off();
}

