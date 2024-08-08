BITS 16
ORG 0x7C00

_start:
    ; Set stack segment
    mov ax, 0x9000
    mov ss, ax
    mov sp, 0xFFFE

    ; Set data segment
    mov ax, 0x0000
    mov ds, ax

    ; Set video mode
    mov ax, 0x0003
    int 0x10

    ; Print "Y" Character (cuz why)
    mov ax, 0x0e59
    int 0x10


; IDT
idt_start:
    ;idt entries

idt_end:
    idt_descriptor:
        dw idt_end - idt_start - 1
        dd idt_start

    lidt [idt_descriptor]


; GDT
gdt_start:
    dd 0x00000000, 0x00000000


    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0x9A
    db 0xCF

    dw 0xFFFF
    dw 0x0008
    db 0x08
    db 0x9A
    db 0xCF

gdt_end:
    gdt_descriptor:
        dw gdt_end - gdt_start - 1
        dd gdt_start

    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:start_pm

CODE_SEG equ 0x08
DATA_SEG equ 0x00
BITS 32

; Load kernel mode goes here
start_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax



    times 510 - ($-$$) db 0
    dw 0xAA55
