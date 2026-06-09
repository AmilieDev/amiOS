/* 
* Author: Amilie (amilietf)
* Date: 2026-06-09
* Desc: Memset needed for GDT
* Lang: C
*/

#ifndef STRING_H
#define STRING_H

#include <stddef.h>

void *memset(void *dst, int c, size_t n);

/*
    TODO:
        Add memcpy, memmove and memcmp
    
    !! DO THESE IN REASONABLE TIME PLEASE !!
*/

#endif