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
     

