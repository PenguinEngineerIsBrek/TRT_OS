#include "../includes/stdint.h"

void print_char(){}
void set_video(){}

uint32_t int10h(){
    uint8_t ahr;
    asm volatile
    (
        "movb %[ahr], %%ah \n\t"
        : [ahr] "=r" (ahr)
        :
        :"ah"
    );
    switch(ahr){
        case 0x00:
            set_video();
            break;
        case 0x0e:
            print_char();
            break;
        default:
            break;
    }
    return 0x00001000;
}
