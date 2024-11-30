#include <stdint.h>


unsigned char port_byte_in(unsigned short port){
// First time using __asm__ syntax in steps_to_make_driver.md 
    unsigned char res;			
    __asm__("in %%dx,%%al":"=a"(res):"d"(port));
    return res;			      	   
}

void port_byte_out(unsigned short port,unsigned char data){ 
     __asm__("out %%al,%%dx"::"a"(data),"d"(port));
}
     
void stringaddr(char *ptr, char *buffer) {
    const char *hex_digits = "0123456789ABCDEF";
    uintptr_t address = (uintptr_t)ptr; // Convert char* to integer type
    int i = 0;

    buffer[i++] = '0';
    buffer[i++] = 'x'; // Add "0x" prefix for hex representation

    if (address == 0) {
        buffer[i++] = '0';
    } else {
        // Process each nibble (4 bits) from most significant to least significant
        int started = 0; // Flag to avoid leading zeros
        for (int shift = (sizeof(char*) * 8) - 4; shift >= 0; shift -= 4) {
            char digit = hex_digits[(address >> shift) & 0xF];
            if (digit != '0' || started) {
                buffer[i++] = digit;
                started = 1; // Start adding digits after the first non-zero
            }
        }
    }

    buffer[i] = '\0'; // Null-terminate the string
    return;
}

