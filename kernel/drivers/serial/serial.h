/* 
* Author: Amilie (amilietf)
* Date: 2026-06-09
* Desc: Serial driver for output to ports.
* Lang: C
*/

#ifndef SERIAL_H
#define SERIAL_H

int init_serial(void);
int transmit_empty(void);
void serial_putchar(char c);
void serial_write(const char *s);
char serial_getchar(void);

#endif