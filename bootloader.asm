[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl
mov bp, 0x9000
mov sp, bp

mov ah, 0x0e 
mov al, '1'
int 0x10
mov al, '6'
int 0x10
mov al, 'B'
int 0x10
mov al, 'i'
int 0x10
mov al, 't'
int 0x10

call load_kernel
call switch_pm
jmp $


%include "./bootloader2.asm"
%include "./print.asm"
%include "./gdt.asm"
%include "./printpm.asm"
%include "./load_disk.asm"
%include "./print_hex.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET
    mov ah, 0x02
    mov al, 35
    mov ch, 0
    mov cl, 2
    mov dh, 0
    int 0x13
    ret


[bits 32]
BEGIN_PM:
    mov ebx, HELLO32BIT
    call print_string_pm
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE db 0
HELLO16BIT db "Starting in 16 bit mode..", 0
HELLO32BIT db "Loaded 32-bit mode...", 0
KERNELLOADMSG db "Loading kernel into memory", 0
times 510-($-$$) db 0 
dw 0xaa55

