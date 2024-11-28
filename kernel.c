#include "drivers/disp.h"
#include "drivers/keyboard.h"
#include "isr.h"
#include "idt.h"


void main() {
    //cls();
    print_s("fcbdshcjbsdhjcfbdsh");
    
    print_s("installing isrs \n");
    isr_install();
    print_s("enabeling external interrupts \n");
    asm volatile("sti");
    
    print_s("init keyboard");
    init_keyboard();
    
}
