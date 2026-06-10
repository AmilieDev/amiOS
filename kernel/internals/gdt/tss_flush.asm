; 
; Author: Amilie (amilietf)
; Date: 2026-06-09
; Desc: Flushing the TSS as part of userspace later.
; Lang: ASM
;

global tss_flush
tss_flush:
    mov ax, 0x28 ; tss selector at index 5
    ltr ax
    ret