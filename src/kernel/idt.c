#include "../includes/stdint.h"
#include "idt.h"

idt_entry_t_32 idt_t[256];
idtr_32_t idtr_t;
void add_interrupt(int n, uint32_t addr, uint16_t selector, uint8_t attr){
    idt_t[n].offset_1 = addr & 0xFFFF;
    idt_t[n].selector = selector;
    idt_t[n].zero = 0x00;
    idt_t[n].type_attributes = attr;
    idt_t[n].offset_2 = (addr >> 16)& 0xFFFF;

}
void setup_idt(){
    add_interrupt(10, 0x00001000, 0x08, 0x8e);
    add_interrupt(13, 0x00001300, 0x08, 0x8e);
    idtr_t.limit = sizeof(idt_t) - 1;
    idtr_t.base = (uint32_t)&idt_t;
    asm volatile
    (
        "lidt %[idtr]\n"
        :
        : [idtr] "m" (idtr_t)
    );
}
