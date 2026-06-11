/* 
* Author: Amilie (amilietf)
* Date: 2026-06-09
* Desc: Memset needed for GDT
* Lang: C
* Resources: https://www.geeksforgeeks.org/cpp/write-memcpy/
*/

#include <stddef.h>

// Simple memset for utilisation in GDTs / TSS.
void *memset(void *dst, int c, size_t n) {
    unsigned char *p = (unsigned char *)dst;
    for (size_t i = 0; i < n; i++) p[i] = (unsigned char)c;
    return dst;
}

void *memcpy(void* dst, const void* src, size_t n){
    char* d = (char*)dst;
    const char* s = (const char*)src;

    for(size_t i = 0; i < n; i++){
        d[i] = s[i];
    }
    return dst;
}