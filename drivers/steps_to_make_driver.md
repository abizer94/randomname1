__asm__ c syntax __asm__("instruction":output operandands:clobbered registers)
__asm__("in %%dx,%%al":"=a"(res):"d"(port)); here it says in dx,al store input from io port specified in dx 
al register  then =a says output is stored in eax ie al should also be stored in res variable in the c code  the last part 
__asm__("out %%al,%%dx"::"a"(data),"d"(port)); does something similar and says that port variable in c should
be stored in dx register before execution of instruction it basically translates to 
mov dx port ;
in dx al;
char res = ax; 
obviously we cannot assign char res = ax  
but this is the closest translation i could think of

1. making a video driver (VGA since its simple) and doesnt need me to read the docs for nvidia and ryzen
	
	a. in vga we have a lot of registers we can read and write to
	but the communication is done via 2 registers mainly  
	ctrl 0x3d4 we write which ctrl register we want to modify to this 
	data 0x3d5 we write the value we want to give to this one
	
	
	b. lets make a functional cursor first vga stores cursor position as low and high byte offset
	   0x0f has low byte of the cursor pos 
	   0x0e had the high byte of pos
	   
	c. screen in vga is in 25x80 character cells that take 2 bytes each in memory first byte for ascii val 
	   of character and second byte as a attribute of the char ie color we will be specifying memory 
	   offset but vga is in terms of character cells so we must divide by 2 to get the correct pos
	   also offset is 16 bit value that needs to be divided into 2 8bit values to give correct pos
	   eg we want to set offset 160
	   offset is 160 divide by 2 to get 80 (binary 00000000 01010000)
	   when right shifted by 8 we get 0 ie the high byte is 0
	   when and with 0xff we get 01010000 ie 80 so low byte is 80 we will get cursor position 
	   on the last character cell of line 1
	   
	   similar logic is used in get cursor pos
	   
	d. 
	    
	   
	   
