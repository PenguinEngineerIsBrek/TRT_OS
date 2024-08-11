#include "idt.h"
#define VGA_BASE 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

volatile uint16_t* vga_buffer = (volatile uint16_t*)VGA_BASE;

void print_char_at(char c, uint8_t row, uint8_t col, uint8_t color) {
    if (row >= VGA_HEIGHT || col >= VGA_WIDTH) {
        return;
    }

    uint16_t offset = (row * VGA_WIDTH) + col;

    vga_buffer[offset] = (color << 8) | c;
}


void print_char(char c, uint8_t color) {
    static uint8_t cursor_x = 0;
    static uint8_t cursor_y = 0;

    print_char_at(c, cursor_y, cursor_x, color);

    cursor_x++;
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
        if (cursor_y >= VGA_HEIGHT) {
            cursor_y = 0;
        }
    }
}


void _start(){
    setup_idt();
    print_char('Y', 0x0F);
}
