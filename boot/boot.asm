; Author: Amilie (amilietf)
; Date: 2026-06-07
; Desc: Primary booter and jumper into Protected Mode
; Lang: x86 Assembly

[org 0x7c00]
[bits 16]
KERNEL_OFFSET equ 0x1000
boot_start:
    cli

    xor ax, ax
    mov ds, ax
    mov es ,ax
    mov ss, ax
    mov sp, 0x7c00
    mov [BOOT_DRIVE], dl ; Move the boot drive from DL.

    mov bx, KERNEL_OFFSET ; set our in boot destination to 1Kb
    mov dh, 16 ; sectors to read
    mov dl, [BOOT_DRIVE]
    call disk_load

    cli
    lgdt [GDT_Descriptor]
    ; change last bit to 1 of cr0
    mov eax, cr0
    or eax, 1
    mov cr0, eax ; yay 32bit!

    jmp CODE_SEG:start_protected_mode

; boot drive management shit
disk_load:
    pusha
    push dx
    mov ah, 0x02 ; read the sectors
    mov al, dh
    mov ch, 0x00 ; cyl and head 0
    mov dh, 0x00
    mov cl, 0x02 ; sectors 2, sect 1 is the boot sector
    int 0x13 ; disk reading
    jc disk_error
    pop dx
    cmp al, dh ; al means that the sectors have read - which is good
    jne disk_error
    popa
    ret

disk_error:
    mov si, DISK_MSG
    call print_string
    jmp $

print_string:
    pusha
    mov ah, 0x0e

.next:
    lodsb
    test al, al
    jz .done
    int 0x10
    jmp .next
.done:
    popa
    ret

BOOT_DRIVE: db 0
DISK_MSG   db "Disk read error", 0

GDT_Start:
    null_descriptor:
        dd 0 ; 4x 00000000
        dd 0 ; 4x 00000000

    code_descriptor:
        ; first 16b of limit
        dw 0xffff
        dw 0
        db 0
        db 10011010b ; pres, priv, type
        db 11001111b ; type flags
        db 0

    data_descriptor:
    ; first 16b of limit
        dw 0xffff
        dw 0
        db 0
        db 10010010b ; pres, priv, type
        db 11001111b ; type flags
        db 0

    GDT_End:

GDT_Descriptor:
    dw GDT_End - GDT_Start - 1 ; size
    dd GDT_Start ; start

CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start
; equ for setting constants

[bits 32]
start_protected_mode:
    ; just clear shit up rq
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp

    ; this output is redundant now tho
    mov byte [0xb8000], 'B'   ; proof we reached protected mode (we need  this to even confirm boot lol)
    mov byte [0xb8001], 0x0f

    call KERNEL_OFFSET
    jmp $

; tell BIOS we are bootable
times 510-($-$$) db 0
db 0x55, 0xaa