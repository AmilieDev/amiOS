/* 
* Author: Amilie (amilietf)
* Date: 2026-06-07
* Desc: Primary init for the kernel, sets everything off!
* Lang: C
*/

#include "drivers/video/vga.h"
#include "memory/gdt.h"
#include "userspace/logging/logging.h"

void init(void) {
    report_status("GDT", init_gdt()); // Setting up the new GDT.
    report_status("VGA", init_vga()); // Init VGA and output basic information.
    report_status("GDT", 0); // GDT *does* work if we get past VGA. This is just the best way to implement a showcase without reiniting again.

    // Standard identifying outputs. Nothing much.
    print_to_screen("\n\n\n\n\n\nWelcome to the amiOS Kernel\n");
    print_to_screen("You are now in debug mode.\n");
}