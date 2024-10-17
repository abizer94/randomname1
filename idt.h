#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint_t)(((address)>>16) & 0xFFFF)


typedef struct{
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
}__attribute__((packed)) idt_gate_t;

idt_gate_t idt[265];
void set_idt_gate(int n,uint32_t handler){
   idt[n].low_offset = low_16(handler);
   idt[n].selector = 0x08;
   idt[n].always0 = 0;
   idt[n].flags=0x8E;
   idt[n].high_offset = high_16(handler);
}


