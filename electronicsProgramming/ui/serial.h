#ifndef __serial_h_
#define __serial_h_

void get_char(volatile unsigned char *pins, unsigned char pin, char *rxbyte);
void put_char(volatile unsigned char *port, unsigned char pin, char txchar);
void put_ram_string(volatile unsigned char *port, unsigned char pin, char *str);

#define max_buffer 25

#endif // __serial_h_
