#ifndef IDT_H
#define IDT_H
#include "../includes/stdint.h"
typedef struct {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attributes;
    uint16_t offset_2;
} __attribute__((packed)) idt_entry_t_32;

typedef struct{
    uint32_t base;
    uint16_t limit;
} __attribute__((packed)) idtr_32_t;

void add_interrupt(int n, uint32_t addr, uint16_t selector, uint8_t attr);

void setup_idt();
#endif
