#include "drivers/disp.h"
#include "drivers/keyboard.h"
#include "isr.h"
#include "idt.h"
#include "mem.h"
#include "shell.h"


void main(){
    //cls();
    
    print_s("installing isrs \n");
    isr_install();
    print_s("enabeling external interrupts \n");
    asm volatile("sti");
    
    print_s("init keyboard");
    init_keyboard();
    allocate_first();
    //cls();
    //pribnr();
    
    int n =5;
    char *ptr = (char*) alloc(n*sizeof(char));
    for(int i = 0;i<n;i++){
    	ptr[i] = 'A'+i;
    }
    for(int i = 0;i<n;i++){
    	print_c(ptr[i]);
    }
    char addr[60];
    stringaddr(ptr,addr);
    
    print_s("the first pointer stored");
    print_s(addr);
    
    freee(ptr);
    char *ptr2 = (char*) alloc(n*sizeof(char));
    for(int i = 0;i<n;i++){
    	ptr2[i] = 'A'+(2*i);
    }
    stringaddr(ptr2,addr);
    print_s("the second pointer stored");
    print_s(addr);
}
