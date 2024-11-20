#include "./drivers/disp.h"
//#include "./drivers/keyboard.h"
//#include "isr.c"
//#include "idt.c"


void main() {
    cls();
    print_s("fcbdshcjbsdhjcfbdsh");
    cls();
    print_s("installing isrs \n");
    //isr_install();
    print_s("enabeling external interrupts \n");
    //asm volatile("sti");
    
    print_s("init keyboard");
    //init_keyboard();
    
}
