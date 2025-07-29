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
    init_paging();
    init_timer(50);
    while (inb(0x64) & 1) inb(0x60);
    outb(0x21, 0xFD);
    for(int i = 1; i < 1024; i++){
        testpagetable = (pagetable_t*)alloc();
        for(int j = 0; j < 1024; j++){
            map_pagetableentry(testpagetable, j);
        }
        map_pagedirentry(pagedir, i, testpagetable);
    }
    volatile uint32_t* ptr = (uint32_t*)0x3FFFFF;
    *ptr = 1234;
    asm volatile("sti");
}
