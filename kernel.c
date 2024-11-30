#include "drivers/disp.h"
#include "drivers/keyboard.h"
#include "isr.h"
#include "idt.h"
#include "mem.h"

void execute_command(char* in){
	if(compare(in,"EXIT")==0){
		print_s("stoppint the CPU byeee");
		asm volatile("hlt");
	}
	print_s("unknown command ");
	print_s(in);
	print_s("\n");
}

void main() {
    //cls();
    int allocate_first();
    print_s("installing isrs \n");
    isr_install();
    print_s("enabeling external interrupts \n");
    asm volatile("sti");
    
    print_s("init keyboard");
    init_keyboard();
    
    cls();
    pribnr();
    
    int n =5;
    char *ptr = (char*) alloc(n*sizeof(char));
    char *ptr2 = (char*) alloc(n*sizeof(char));
    for(int i = 0;i<n;i++){
    	ptr[i] = 'A'+i;
    	ptr2[i] = 'A'+i;
    }
    for(int i = 0;i<n;i++){
    	print_c(ptr[i]);
    }
    char addr[60];
    stringaddr(ptr,addr);
    
    print_s("the first pointer stored");
    print_s(addr);
    stringaddr(ptr,addr);
    print_s("the second pointer stored");
    print_s(addr);
    freee(ptr);
}
