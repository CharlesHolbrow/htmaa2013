#ifndef __input_h_
#define __input_h_

#define button_up() (PINA & (1 << 3))
#define button_down() (!button_up())
#define water() (!(PINA & (1 << 2)))

void init_input();

#endif // __input_h_
