#ifndef __led_h_
#define __led_h_

// LED     PA7 (pin 6)
#define led_on() bit_set(PORTA, BIT(7))
#define led_off() bit_clear(PORTA, BIT(7))

void blink(int seconds);
void init_led();

#endif // __led_h_
