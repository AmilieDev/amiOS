; Author: Amilie (amilietf)
; Date: 2026-06-07
; Desc: Handoff from the main boot.asm into the init.c via linker.ld
; Lang: x86 Assembly

[bits 32]
[extern init]
global _start

_start:
    call init ; pretty self explainatory i think lmfao
    jmp $