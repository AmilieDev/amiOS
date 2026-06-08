// TODO: Implement a userspace GDT

/* 
* Author: Amilie (amilietf)
* Date: 2026-06-08
* Desc: Basic GDT struct post loader handoff.
* Lang: C
*/

#include <stdint.h>
#include "gdt.h"

struct gdt_entry{
    uint16_t limit_low; // sets the size of the bits between 0 to 15
    uint16_t base_low; // is the start address in 0-15
    uint8_t base_mid; // is the start address in 16-23
    uint8_t access; // sets the permissions
    uint8_t flags_limit; // is the flags + size bits of 16-19
    uint8_t base_high; // start addr 24-31
}__attribute__((packed));

struct gdt_ptr{
    uint16_t limit; // tbl size - 1
    uint32_t base; // table address
}__attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gdtr;

extern void gdt_flush(uint32_t); // see asm file gdt_flush.asm

// prepares for the entries to be set for various parts of the gdt
void set_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags){
    gdt[i].limit_low = limit & 0xFFFF;
    gdt[i].base_low = base & 0xFFFF;
    gdt[i].base_mid = (base  >> 16) & 0xFF;
    gdt[i].access = access;
    gdt[i].flags_limit = ((limit >> 16) & 0x0F) | (flags << 4);
    gdt[i].base_high = (base  >> 24) & 0xFF;
}

// does what it says on the tin, initializes the gdt
int init_gdt(void) {
    set_entry(0, 0, 0, 0, 0); // Null first entry. Must be all zeros for GDT.
    set_entry(1, 0, 0xFFFFF, 0x9A, 0xC); // basically the same as in the boot.asm, this is code params
    set_entry(2, 0, 0xFFFFF, 0x92, 0xC); // data params with 0x92
    gdtr.limit = sizeof(gdt) - 1;
    gdtr.base = (uint32_t)&gdt;
    gdt_flush((uint32_t)&gdtr);
    return 0;
}