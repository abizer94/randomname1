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

1. Making a video driver (VGA since its simple) and doesnt need me to read the docs for nvidia and ryzen
	
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
	
	d. we need to make it scroll too so if offset is greater than 80*2*(number of rows we want to see on screeen)
	if so we move all characters up one row and move cursor up one step
	    
	    
2. Making a keyboard drivern once again I will use a older version PS/2 keyboard since usb keyboards
   have a much more complex structure with usb host controller to handle usb comms and a specific 
   keyboard driver 

	a. keyboard drivers are significantly more annoying to make than a vga driver since we need to setup a
	IDT (interrupt discriptor table) basically with the PS/2 device there was a microcontroller that 
	recieved the inputs stores info to port 0x60 and then sends an interrupt to the cpu
	
	b. The cpu looks up how it needs to handle an interrupt in the IDT so the IDT has 256 entries
	 each 8 bytes long for each type of interrupt it can come across
	 There are 3 types of entries it can have 
	 1. Interrupt gates 
	 2. Trap gates
	 3. Task gates 
	Interrupt and Trap gates can call custom handeler functions (ISR Interrupt service routine)
	Task gates are used to switch bw tasks to multitask the current state of a process is saved in a TSS task state segment and the TSS of the other task is loaded up 
	c. for this one we just need to do the Interrupts and not the rest
	
	info for interrupt gates 
	1 offset 32 bit representation in memory address of the interrupt handler within the respective code seg
	2 selector 16 bit selector code seg to jump to when invoking the handler this will be the kernel code seg
	3 type 3 bits indicating gate type will be set to 110 for interrupt
	4 1 bit sayinng if it is 32 bit code segment or not
	5 2 bits showing privilage level we will set it to 00
	6 1 bit showing if gate is active
	7 some bits need to always be 0 in interrupt gates idk why 
	
	d. Making ISR for the keyboard
	
	the first 32 ISRs are reserved for CPU specific interrupts like exceptions and faults setting 
	these up is important since its how we know where we messed up in the later steps of defining irqs 
	
	1 first we define a general isr handler in c it will extract all necessary info related to an 
	interrupt and act accordingly 
	a. we will just define a simple array that has string representation of all the interrupt numbers
	
	
