/* 
* Author: Amilie (amilietf)
* Date: 2026-06-09
* Desc: The task state segment loader for GDTs in userspace and future multitasking.
* Lang: C
*/

#include <stdint.h>
#include "gdt.h"
#include "tss.h"
#include "../../lib/string.h"

struct tss_entry tss;

int init_tss(void){
    uint32_t base = (uint32_t)&tss;
    uint32_t limit = sizeof(tss) - 1;

    set_entry(5, base, limit, 0x89, 0x00);

    memset(&tss, 0, sizeof(tss));

    // we gotta set these 2 to zero to make sure alignment isnt knocked off
    tss.ss0 = 0x10;
    tss.esp0 = 0;
    tss.iomap_base = sizeof(tss);

    // calls the asm in tsa_flush.asm
    tss_flush();
    return 0;
}