#include "disp.h"
#include "../isr.h"
#include <stdbool.h>
#include "../kernel.h"
#include "../shell.h"

#define Max_sc 57
#define back 0x0E
#define enter 0x1C

static char keyarr[256];

const char code[] = {
  '?', '?', '1', '2', '3', '4', '5',
  '6', '7', '8', '9', '0', '-', '=',
  '?', '?', 'Q', 'W', 'E', 'R', 'T',
  'Y', 'U', 'I', 'O', 'P', '[', ']',
  '?', '?', 'A', 'S', 'D', 'F', 'G',
  'H', 'J', 'K', 'L', ';', '\'', '`',
  '?', '\\', 'Z', 'X', 'C', 'V', 'B',
  'N', 'M', ',', '.', '/', '?', '?',
  '?', ' '
};

int strl(char s[]){
	int i = 0;
	while (s[i]!= '\0'){
		i++;
	}
	return i;
}

bool append(char s[] , char n){
	int len = strl(s);
	if(len>=256)return false;
	s[len] = n;
	s[len+1] = '\0';
	return true;
}
bool backspace(char s[]){
	int len = strl(s);
	if(len>0){
		s[len-1] = '\0';
		return true;
	}
	else{
		return false;
	}
	
}

int compare(char s1[] ,char s2[]){
	int i;
	for(i =0;s1[i]==s2[i];i++){
		if(s1[i]==' ') return 0;
	}
	return s1[i]-s2[i];
}


static void keyboard_call(registers_t *rgs){
    uint8_t scancode = port_byte_in(0x60);
    if(scancode>Max_sc)return;
    if(scancode == back){
    	if(backspace(keyarr)){
    	print_back();
    	}
    }else if(scancode == enter){
    	nl();
    	exec(keyarr);
    	keyarr[0] = '\0';
    }else{
    char letter = code[(int) scancode];
    
    if(append(keyarr,letter)){
    	char str[2] = {letter,'\0'};
    	print_s(str);
    }
    }
}

void init_keyboard(){
    register_interrupt_handler(IRQ1,keyboard_call);

}

