#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "led.h"
#include "button.h"
#include "audio.h"
#include "mixer.h"
#include "sequencer.h"
#include "song.h"
#include "uart.h"

static uint8_t cur_song;

void init(void) {
    // Initialize the various subsystems
    led_init();
    button_init();
    uart_init();
    audio_init();
    mixer_init();
    sequencer_init();

    // Enable interrupts
    sei();
}

// Main program loop
void loop() {
    for(;;) {
        mixer_task();
        sequencer_task();

        if(button_pressed()) {
            if(++cur_song >= N_SONGS) {
                cur_song = 0;
            }
            uart_putdata((unsigned char*)"Playing song ", 13);
            uart_putchar('1' + cur_song);
            uart_putchar('\r');
            uart_putchar('\n');
            sequencer_load(songs[cur_song]);
        }
    }
}

int main(void) {
    cur_song = 255;
    init();
    loop();
    return 0;
}
