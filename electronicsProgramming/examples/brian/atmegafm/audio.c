#include <avr/io.h>
#include "audio.h"

void audio_init(void) {
    // Set up Timer 1 for PWM output at a high frequency; this is how we'll drive 
    // "analog" voltage levels into the speaker.  Since the PWM frequency is high,
    // we can use the speaker's inductance to do the low-pass filtering. With a 
    // 20 MHz system clock, and 8 bits of PWM resolution, the PWM frequency will
    // be 78.125 kHz.
    
    //DDRB |= (1<<PB1);
    //TCCR1A = (1<<COM1A1) | (1<<WGM10);
    //TCCR1B = (1<<WGM12) | (1<<CS10);
    //OCR1A = 0;
    
    DDRB |= (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3) | (1<<PB4);
    DDRD |= (1<<PD5) | (1<<PD6) | (1<<PD7);
}

void audio_output(uint8_t sample) {
    uint8_t tempd = PORTD & ~( (1<<PD7) | (1<<PD6) | (1<<PD5) );
    uint8_t tempb = PORTB & ~( (1<<PB0) | (1<<PB1) | (1<<PB2) | (1<<PB3) | (1<<PB4));

    tempd |= (sample & 0x7) << 5;
    tempb |= (sample & 0xF8) >> 3;

    PORTD = tempd;
    PORTB = tempb;
}

