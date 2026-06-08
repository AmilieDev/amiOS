/* 
* Author: Amilie (amilietf)
* Date: 2026-06-07
* Desc: VGA preparation, and utils for writing to display.
* Lang: C
*/

#include "vga.h"
#include "../io.h"

static volatile unsigned short *const vga = (volatile unsigned short *)0xb8000; // <- Prepare to write to video memory.
static int cursor_row = 0;
static int cursor_col = 0;

void init_vga(void){
    // disable cursor on init
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);

    for (int i = 0; i < 80 * 25; i++)
        vga[i] = 0x0f20; // Clear the screen.
}

void newline(void){
    cursor_col = 0;
    if(++cursor_row >= 25)
        scroll(); // We ran off the lines, so this will scroll.
}

void putchar(char c){
    if(c == '\n'){
        newline();
        return;
    }
    vga[cursor_row * 80 +cursor_col] = (0x0f << 8) | c;
    if(++cursor_col >= 80)
        newline(); // We hit the end of the line (80 long) so we put a new line.
}

void scroll(void){
    // move rows 1..24 up to 0..23
    for(int i = 0; i < 24 * 80; i++)
        vga[i] = vga[i + 80];
    // we gotta cleaer the shit out now
    for(int i = 24 * 80; i < 25 * 80; i++)
        vga[i] = 0x0f20;
    cursor_row = 24; // stick to the bottom tho
}

void print_to_screen(const char *msg){
    for (int i = 0; msg[i]; i++)
        putchar(msg[i]);
}