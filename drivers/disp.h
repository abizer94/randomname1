#define VGA_CTR_REG 0x3d4
#define VGA_DATA_REG 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
unsigned char port_byte_in(unsigned short port){// First time using __asm__ syntax in steps_to_make_driver.md 
unsigned char result;			
    __asm__("in %%dx,%%al":"=a"(res):"d"(port));
return res;			      	   
}
void port_byte_out(unsigned short port){ 
     __asm__("out %%al,%%dx"::"a"(data),"d"(port));
     }
     
			   
void set_cursor(int offset){
     offset /=2;			   
     port_byte_out(VGA_CTR_REG,VGA_OFFSET_HIGH);
     port_byte_out(VGA_DATA_REG,(unsigned char)(offset>>8));
     port_byte_out(VGA_CTR_REG,VGA_OFFSET_LOW);
     port_byte_out(VGA_DATA_REG,(unsigned char)(offset&0xff));
     }
     
int get_cursor(){
	port_byte_out(VGA_CTR_REG,VGA_OFFSET_HIGH);
	int offset = port_byte_in(VGA_DATA_REG)<<8;
	port_byte_out(VGA_CTR_REG,VGA_OFFSET_LOW);
	offset += port_byte_in(VGA_DATA_REG);
	return
}





