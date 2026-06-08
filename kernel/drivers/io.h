/* 
* Author: Amilie (amilietf)
* Date: 2026-06-07
* Desc: For disabling the cursor, and other IO interactions later.
* Lang: C
*/

#ifndef IO_H
#define IO_H

static inline void outb(unsigned short port, unsigned char val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

#endif