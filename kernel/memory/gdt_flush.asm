; 
; Author: Amilie (amilietf)
; Date: 2026-06-08
; Desc: Flushing the GDT.
; Lang: ASM
;

global gdt_flush
gdt_flush:
    mov eax, [esp + 4]
    lgdt [eax]
    jmp 0x08:.reload
.reload:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret