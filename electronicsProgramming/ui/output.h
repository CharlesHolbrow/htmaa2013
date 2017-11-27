#ifndef __output_h_
#define __output_h_

// Output Compare Register 0B can generate pwm on pin 6
#define led_level(v) OCR0B = (v)

// Output Compare Registers are Compared with counter on each clock cycle
// Output Compare Register 0A can generate pwm on pin 5
#define out_duty(v) OCR0A = (v)

void init_pwm();
void audio_off();
void audio_on();

void init_audio_clock();

#endif // __output_h_
