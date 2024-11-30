#include "idt.h"


idt_gate_t idt[256];
idt_register_t idt_reg;

void set_idt_gate(int n,uint32_t handler){
   idt[n].low_offset = low_16(handler);
   idt[n].selector = 0x08;
   idt[n].always0 = 0;
   idt[n].flags=0x8E;
   idt[n].high_offset = high_16(handler);
}

void load_idt(){
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = 256 * sizeof(idt_gate_t) - 1;
    asm volatile("lidt (%0)": :"r"(&idt_reg)); // volatile is a modifyer in c that tells the compiler that this instruction should not be optamised sometimes the compiler may remove certain instructions or it may remove it from loop and cache this stops it usually it may do this for instructions that have no dependencies 
}
