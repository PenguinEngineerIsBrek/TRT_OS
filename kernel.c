#include <stdint.h>
#include "./std/io.h"
#include "./std/stdbool.h"
#include "./drivers/vga.h"
#include "./idt.h"
#include "./irq.h"
#include "./std/util.h"
#include "./drivers/keyboard.h"
#include "./drivers/timer.h"
#include "./mmu/pagedir.h"
extern void print_hex;
pagetable_t* testpagetable;
void main(){
    clear_screen();
    idt_init();
    init_timer(50);
    while (inb(0x64) & 1) inb(0x60);
    outb(0x21, 0xFD);
    for(int i = 0; i < 1024; i++){
        testpagetable = allocpagetable();
        map_pagedirentry(pagedir, i, testpagetable);
    }
    init_paging();
    volatile uint32_t* ptr = (uint32_t*)0x07FFFFFC;
    *ptr = 1234;
    asm volatile("sti");
}
