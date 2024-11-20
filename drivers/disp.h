#pragma once
#define VGA_CTR_REG 0x3d4
#define VGA_DATA_REG 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define V_ADDR 0xb8000
#define MAX_R 25
#define MAX_C 80
#define W_ON_B 0x0f


unsigned char port_byte_in(unsigned short port){
// First time using __asm__ syntax in steps_to_make_driver.md 
    unsigned char res;			
    __asm__("in %%dx,%%al":"=a"(res):"d"(port));
    return res;			      	   
}

void port_byte_out(unsigned short port,unsigned char data){ 
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
	return offset*2;
}

void set_char_in_mem(char c,int offset){
	unsigned char *vidm = (unsigned char *) V_ADDR;
	vidm[offset]=c;
	vidm[offset+1]=W_ON_B;
}

int get_row_from_offset(int offset) {
    return offset / (2 * MAX_C); 
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_C + col);
}

int mov_offset_nl(int offset){
	return get_offset(0,get_row_from_offset(offset)+1);
}

void cpy_chk(char * src,char*dst,int nbytes){
	int i;
	for(i =0;i<nbytes;i++){
		*(dst+i)=*(src+i);
	}
}

int scr_ln(int offset){
	cpy_chk(
	(char*)(get_offset(0,1)+V_ADDR),
	(char*)(get_offset(0,0)+V_ADDR),
	MAX_C*(MAX_R-1)*2
	);
	for(int c =0;c<MAX_C;c++){
		set_char_in_mem(' ',get_offset(c,MAX_R-1));
	}
	return offset-(2*MAX_C);
}
void cls(){
    for(int i =0;i<MAX_C*MAX_R;i++){
        set_char_in_mem(' ',i*2);
    }
    set_cursor(get_offset(0,0));
}

void print_s(char* s){
	int offset = get_cursor();
	int i = 0;
	while(*(s+i)!=0){
		if(offset>=20*MAX_C*2){
			offset = scr_ln(offset);
		}
		if(*(s+i)=='\n'){
			offset = mov_offset_nl(offset);
		}else{
			set_char_in_mem((char)*(s+i),offset);
			offset+=2;
		}
		i++;
	}
	set_cursor(offset);
}
void nl(){
	int offset = get_cursor();
	offset = mov_offset_nl(offset);
	set_cursor(offset);
}

