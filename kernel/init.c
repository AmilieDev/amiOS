/* 
* Author: Amilie (amilietf)
* Date: 2026-06-07
* Desc: Primary init for the kernel, sets everything off!
* Lang: C
*/

#include "drivers/video/vga.h"

void init(void) {
    init_vga(); // <- Prepare to write to video memory.

    print_to_screen("[INFO] The amiOS Kernel - Copyright Amilie and Contributors 2026\n");
    print_to_screen("[INFO] You are running a build from the 7th of June 2026.\n");

    // TODO: Move all this into a logging function with actual checks to ensure shit worked.
    print_to_screen("\n[OK] Handoff from bootloader completed.\n"); // kinda has to have worked if were here dumbass
    print_to_screen("[OK] VGA initalized correctly. If you see this, it worked.\n"); // same here idiot
}