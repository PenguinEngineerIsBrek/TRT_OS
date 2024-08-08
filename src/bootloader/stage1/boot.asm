BITS 16                ; 16-bit code
ORG 0x7C00             ; Set the origin to 0x7C00 for boot sector

_start:
    mov ah, 0x0E       ; BIOS teletype output function
    mov al, 'X'        ; Character to print
    int 0x10           ; Call BIOS video interrupt

    cli                ; Disable interrupts
    hlt                ; Halt the CPU

    ; Pad the rest of the sector with zeros
    times 510 - ($ - $$) db 0

    ; Boot sector signature
    dw 0xAA55

    ; The boot sector should be exactly 512 bytes in size.
