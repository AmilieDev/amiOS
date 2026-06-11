/* 
* Author: Amilie (amilietf)
* Date: 2026-06-08
* Desc: Basic GDT struct post loader handoff.
* Lang: C
*/

#ifndef GDT_H
#define GDT_H
#include <stdint.h>

int init_gdt(void);
void set_entry(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif