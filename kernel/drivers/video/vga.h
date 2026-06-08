/* 
* Author: Amilie (amilietf)
* Date: 2026-06-07
* Desc: VGA preparation, and utils for writing to display.
* Lang: C
*/

#ifndef VGA_H
#define VGA_H

int init_vga(void);
void newline(void);
void putchar(char c);
void scroll(void);
void print_to_screen(const char *msg);

#endif