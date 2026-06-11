// todo: implement an idt table
// Resources : https://samypesse.gitbook.io/how-to-create-an-operating-system/chapter-7

#include "idt.h"
#include <stdint.h>

#define IDTBASE 0x000000000
#define IDTSIZE 0xFF
idtr kidtr;

struct idtr{
    uint16_t limit;
    uint32_t base;
} __attribute__ ((packed));

struct idtdesc{
    uint16_t offset0_15;
    uint16_t select;
    uint16_t type;
    uint16_t offset16_31;
} __attribute__ ((packed));

void init_idt_desc(uint16_t select, uint32_t offset, uint16_t type, struct idtdesc *desc){
    desc->offset0_15 = (offset & 0xFFFF);
    desc->select = select;
    desc->type = type;
    desc->offset16_31 = (offset 0xFFFF0000) >> 16;
    return;
}

// Used for calling the IDT to initialize in the init functions.
int init_idt(void){
    // todo; implement the idt then implement the void

    // todo; implement memcpy, define idt base  and that sorta shit
    int i;
    for(i = 0; i < IDTSIZE; i++;)
        init_idt_desc(0x08, (uint32_t)_asm_schedule, INTGATE, &kidtr[i]);

    return 0;
}