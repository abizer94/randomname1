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
	Task gates are used to switch bw tasks to multitask the current state of a process is saved 
	in a TSS task state segment and the TSS of the other task is loaded up 
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
	
	the first 32 ISRs are reserved for CPU specific interrupts
	this is important since its how we know where we messed up in the later steps of defining irqs 
	
	1 first we define a general isr handler in c it will extract all necessary info related to an 
	interrupt and act accordingly 
	a. we will just define a simple array that has string representation of all the interrupt numbers
	b. a handler function that just prints the exception message if ine occurs 
	c. making a structure for all the register values in c 
	
	since c doesnt have direct access to the registers
	 we can add the registers to stack and push a stack pointer and call the function the way C works is
	 when a function is called its arguments are stored in the stack in the same order and we use offsets to 
	 get the values so if i have a c function which has a pointer as an argument and i have a memory
	 location pushed to stack then call the function from assembly C will take that memory location
	 we pushed as the argument and we have effectively given C that memory as pointer 
	 
	 in this case we have passed the structure registers_t as the argument and a pointer to stack with all
	 the registers pushed 
	 **the order in which we push registers must match the order we have it in the structure**
	 
	d. now that the C part is done we will do somethign similar in assembly make interrupts.asm and 
		1. add a function for each interrupt service req where we push the error info followed
		by the interrupt number and jump to common procedure
		
		2. common procedure for all interrupts push the registers and set eax to ds and then push eax to
		stack as well now set all segment selectors ax,ds,es,fs,gs to data segemnt in this case 0x10 
		ie 2 ( 0 is null 1 is code 3 is data) we need to do this for all possible segment selectors so 
		that we have freedom to use the rest as we want in later parts if we need to
		
		3. push the stack pointer value to stack and call the C function (we have effectively given the 
		struct registers_t to C) 
		4. after we have returned back to assembly we should pop the stack pointer and pop the original 
		value of ds to eax and use it to set all the segment selectors back to their original values
		and move the stack pointer back by 2 as well since we dont need the error code and interrupt no 
		anymore
	e. now we will add all the irq and isrs to the idt we have the idt as an array that holds 
		1. the low 16 bits of the address to the function that handles the interrupt 
		2 the offset in the code segment
		3. flags for the idt entry 
		4. the high 16 bits of the address to the handler function 
	   once we have set all of these in the array we can use lidt to load the idt to the cpu
	
	
	f. reprogramming the PIC (programmable interrupt controller) we now use wither the APIC or the USB 
	   by default the bios programms the pic in 16 bit real mode with the first 8 gates in tand the first 8 
	   IRQs this in 32 bit mode conflicts with the cpu reserved interrupts so we need to remap them so there 
	   are no conflicts we will do this by using port 0x20 and 0x21 for command and data for pic1 and port 
	   0xA0 and 0xA1 for pic2 the programming starts by sending the ICWs we will do this in the isr install 
	   function 
	   
	   	ICW1 send 0x11 (00010001) to both PICs from right to left here is that the bits mean
	   		0. 1 if ICW4 is required 0 if not
	   		1. 1 if single pic is used 0 if cascaded pics is used
	   		2. how many bytes apart is each ISR 0 is 8 bytes 1 is 4 bytes apart
	   		3. edge vs level triggered interrupt 1 is level 0 is edge
	   		4.always 1
	   		5-7. ISR address lower byte segment
	   	    ICW1 signals to the PIC that we are reprogramming it so it will now wait for the following 
	   	    inputs since we enabled ICW4 we need to give it 3 inputs
	   		
	   	ICW2 Set IDT offset 0x20 or 32 for the primary PIC and 0x28 40 for the secondary one 
	   	each one will map 8 gates and since the first 3 gates are reserved for the cpu we will start at 32
	   	
	   	ICW3 set 0x04 for primary and 0x02 for secondary
	   	this basiccally sets the master slave relation of the PICs this tells the master pic which 
	   	IRQs are connected to a slave and tells the slave which ones are connected to master 

	   	This is a 8 bit address each bit represents a irq if there is a slave/master present on the irq 
	   	then it is set to 1 otherwise it is set to 0
	   	
		ICW4 set 0x01 for both
		0. 1 operate in 80x86 mode 0 operates in 80x85 mode 
		1. 1 after finishing the service the pic auto sends the end of interrupt signal 0 it requires 
		   manual end of interrupt
		2. if pic operates on buffer as master its set to 1 
		3. if pic operates on buffera s slave its set to 1
		4. 1 enables fully nested mode for cascaading pic 0 for normal mode
	        5-7. reserved must be set ot 0
	        
	        OCW1 0x00 for both no mask 
	g. setup irq handlers same way as isr handlers but in the C function of irq handler we will have an array 
	of handlers since we want to handle each type of interrupt in a different way so we will change it to an 
	array so that its easily editable the general function looks at the registers and the interrupt number 
	and sets handler to the appropriate handler from the array we made above and executes the handler
	
	after the request is complete we need to manually send the eoi 0x20 signal to the PIC and we need to send to only primary for int 0 to 7 and both for int 8 to 15 
	
	h. loading the IDT we can load the idt descriptor using lidt in assembly so we first need to make the idt descriptor it should have the size limit and the base address of the idt we can then call lidt using asm
	
	        
	        
	   
	   
	   
	   
