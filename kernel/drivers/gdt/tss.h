/* 
* Author: Amilie (amilietf)
* Date: 2026-06-09
* Desc: The task state segment loader for GDTs in userspace and future multitasking.
* Lang: C
*/

#ifndef TSS_H
#define TSS_H
#include <stdint.h>

struct tss_entry {
    uint32_t prev_tss;
    uint32_t esp0, ss0;
    uint32_t esp1, ss1, esp2, ss2;
    uint32_t cr3, eip, eflags;
    uint32_t eax, ecx, edx, ebx;
    uint32_t esp, ebp, esi, edi;
    uint32_t es, cs, ss, ds, fs, gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
} __attribute__((packed));

extern struct tss_entry tss;

int init_tss(void);
void tss_flush(void);   /* defined in your asm */

#endif