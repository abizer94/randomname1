
typedef struct{
	uint32_t ds;
	uint32_t edi,esi,ebp,esp,ebx,edx,ecx,eax;
	uint32_t int_no,errcode;
	uint32_t eip,cs,eflag,useresp,ss;
}registers_t;
void isr_install(){
    set_idt_gate(0,(uint32_t) isr0);
    set_idt_gate(1,(uint32_t) isr1);
    set_idt_gate(2,(uint32_t) isr2);
    set_idt_gate(3,(uint32_t) isr3);
    set_idt_gate(4,(uint32_t) isr4);
    set_idt_gate(5,(uint32_t) isr5);
    set_idt_gate(6,(uint32_t) isr6);
    set_idt_gate(7,(uint32_t) isr7);
    set_idt_gate(8,(uint32_t) isr8);
    set_idt_gate(9,(uint32_t) isr9);
    set_idt_gate(10,(uint32_t) isr10);
    set_idt_gate(11,(uint32_t) isr11);
    set_idt_gate(12,(uint32_t) isr12);
    set_idt_gate(13,(uint32_t) isr13);
    set_idt_gate(14,(uint32_t) isr14);
    set_idt_gate(15,(uint32_t) isr15);
    set_idt_gate(16,(uint32_t) isr16);
    set_idt_gate(17,(uint32_t) isr17);
    set_idt_gate(18,(uint32_t) isr18);
    set_idt_gate(19,(uint32_t) isr19);
    set_idt_gate(20,(uint32_t) isr20);
    set_idt_gate(21,(uint32_t) isr21);
    set_idt_gate(22,(uint32_t) isr22);
    set_idt_gate(23,(uint32_t) isr23);
    set_idt_gate(24,(uint32_t) isr24);
    set_idt_gate(25,(uint32_t) isr25);
    set_idt_gate(26,(uint32_t) isr26);
    set_idt_gate(27,(uint32_t) isr27);
    set_idt_gate(28,(uint32_t) isr28);
    set_idt_gate(29,(uint32_t) isr29);
    set_idt_gate(30,(uint32_t) isr30);
    set_idt_gate(31,(uint32_t) isr31);
}
char *exception_messages[] = {
	"Division by 0 x00",
	"Debug x01",
	"NMI x02",
	"BP x03",
	"Overflow x04",
	"Bound Range Exceeded x05",
	"Invalid Opcode x06",
	"Coprocessor not available x07",
	"Double fault x08",
	"Coprocessor seg overrun x09",
	"Invalid TSS x0A",
	"Segmentation not present x0B",
	"Stack Seg fault x0C",
	"General Protection Fault x0D",
	"Page Fault x0E",
	"Reserved x0F",
	"X87 fl exception x10",
	"alignment Check x11",
	"machine check x12",
	"SIMD FL exception x13",
	"Virtualization exception x14",
	"Control protection exception x15",
	"reserved x16 - x1f",
	"IRQ 0-7 x20 - x27",
	"IRQ 8-15 x70-x77"
};
void isr_h(registers_t *r){
print_s(exception_messages[r->int_no]);
nl();
}

