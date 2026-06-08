/* 
* Author: Amilie (amilietf)
* Date: 2026-06-07
* Desc: Primary init for the kernel, sets everything off!
* Lang: C
*/

#include "drivers/video/vga.h"
#include "memory/gdt.h"

void init(void) {
    // Setting up the new GDT.
    init_gdt(); // build and load

    // Init VGA and output basic information.
    int vga_ret_code = init_vga();

    if(vga_ret_code == 0){
        // TODO: Move all this into a logging function with actual checks to ensure shit worked.
        print_to_screen("\n[OK] Handoff from bootloader completed.\n"); // kinda has to have worked if were here dumbass
        print_to_screen("[OK] GDT initialized successfully.\n");
        print_to_screen("[OK] VGA initalized correctly. If you see this, it worked.\n"); // same here idiot
    }else{
        __asm__ volatile ("hlt");
    }
}