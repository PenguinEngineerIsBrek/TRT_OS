BITS 16
ORG 0x7C00

%macro PRINT_STRING 1
    ; Parameters:
    ;   %1 - Address of the string to print (register or memory address)

    ; Set DS to the correct segment (if needed)
    mov     ax, 0xB800          ; Set DS to video memory segment (0xB800 for color text mode)
    mov     ds, ax              ; Load DS with the segment address

    ; Load the string address into SI
    mov     si, %1

    ; Print characters until we encounter a null terminator (0x00)
print_loop:
    lodsb                       ; Load byte at DS:SI into AL and increment SI
    cmp     al, 0x00            ; Compare AL with null terminator
    je      done                ; If AL == 0x00, end of string
    mov     ah, 0x0E            ; BIOS teletype output function
    int     0x10                ; Call BIOS interrupt
    jmp     print_loop          ; Repeat for next character
done:
%endmacro

%macro wait1s 0 
	MOV     CX, 0FH
	MOV     DX, 4240H
	MOV     AH, 86H
	INT     15H
%endmacro
%macro clearscreen 0
mov ah, 0x00       ; Function to set cursor position
mov bh, 0x00       ; Page number (0 for the default page)
mov cx, 0x0000     ; Starting position (row 0, column 0)
mov dx, 0x184F     ; Ending position (row 24, column 79)
int 0x10           ; Call BIOS interrupt to set cursor position

mov ah, 0x06       ; Function to scroll the window up (clear screen)
mov al, 0x00       ; Attribute byte (default text attribute)
mov bh, 0x00       ; Page number
mov ch, 0x00       ; Starting row
mov cl, 0x00       ; Starting column
mov dh, 0x18       ; Ending row (24)
mov dl, 0x4F       ; Ending column (79)
int 0x10           ; Call BIOS interrupt to scroll and clear

%endmacro
section .data
	msg db "TRT", 0
section .text
	global _start
_start:
	; Stack segment
	mov ax, 0x9000
	mov ss, ax
	mov sp, 0xFFFE
	
	; Data segment
	mov ax, 0x0000
	mov ds, ax

	;Video mode
	mov ax, 0x0003
	int 0x10
	
	mov ah, 0x0e
	mov al, 'B'
	int 0x10
	mov al, 'O'
	int 0x10
	mov al, 'O'
	int 0x10
	mov al, 'T'
	int 0x10
	mov al, 'I'
	int 0x10
	mov al, 'N'
	int 0x10
	mov al, 'G'
	int 0x10
	mov al, 0x20
	int 0x10
	mov al, 'K'
	int 0x10
	mov al, 'E'
	int 0x10
	mov al, 'R'
	int 0x10
	mov al, 'N'
	int 0x10
	mov al, 'E'
	int 0x10
	mov al, 'L'
	int 0x10
	mov al, '.'
	int 0x10
	mov al, '.'
	int 0x10
	mov al, '.'
	int 0x10


	;Boot kernel into memory
	mov ax, 0x7e00
	mov es, ax
	mov ah, 0x02
	mov al, 4
	mov ch, 0
	mov cl, 2
	mov dh, 0
	mov dl, 0x80
	mov bx, 0x0000
	int 0x13

	jmp 0x0000:start_kernel

start_kernel:
	mov ah, 0x02
	mov dx, 0x0100
	mov bh, 0x00
	int 0x10
	mov ah, 0x0e
	mov ax, 0x0010
	mov ds, ax
	mov es, ax
	wait1s
	clearscreen	
	times 510 - ($-$$) db 0
	dw 0xAA55
