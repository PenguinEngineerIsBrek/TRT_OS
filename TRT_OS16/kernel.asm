BITS 16
ORG 0x7e00

section .text
global _start
_start:	
	mov ah, 0x00
	int 0x10
	mov ax, 0x0e58
	int 0x10
	times 512*4 - ($-$$) db 1
	hlt
