/* 
* Author: Amilie (amilietf)
* Date: 2026-06-09
* Desc: Serial driver for output to ports.
* Lang: C
*/

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8
#define COM5 0x5F8
#define COM6 0x4F8
#define COM7 0x5E8
#define COM8 0x4E8

#include "../io.h"
#include "serial.h"
#include <stdint.h>
#include <stddef.h>

int init_serial(void){
    outb(COM1 + 1, 0x00); // disable the interrupts (IER)
    outb(COM1 + 3, 0x80); // set the DLAB to be access advisor
    outb(COM1 + 0, 0x03); // the divisor low byte (the baud rate)
    outb(COM1 + 1, 0x00); // dvisor high byte
    outb(COM1 + 3, 0x03); // 8N1, clears the DLAB LCR
    outb(COM1 + 2, 0xC7); // enable and clear FIFO
    outb(COM1 + 4, 0x0B); // DTR, RTS, OUT2 set

    // do a self test to ensure port owrks
    outb(COM1 + 4, 0x1E); // loopback mode
    outb(COM1 + 0, 0xAE);

    if(inb(COM1 + 0) != 0xAE)
        return 1; // chip is fault / not here

    outb(COM1 + 4, 0x0F); // normal operation
    return 0; // is working
}

int transmit_empty(void){
    return inb(COM1 + 5) & 0x20;
} // THRE bit (transmission buffer)

void serial_putchar(char c){
    while(!transmit_empty());
    outb(COM1, c);
}

void serial_write(const char *s){
    for(size_t i = 0; s[i]; i++){ // cycle thru the chars
        if(s[i] == '\n')
            serial_putchar('\r'); // crlf is a carriage return line feed
    serial_putchar(s[i]);
    }
}

// basic reading capabilites
char serial_getchar(void){
    while(!(inb(COM1 + 5) & 1));
    return inb(COM1);
}