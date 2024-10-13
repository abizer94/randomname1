gdt_start:
	dq 0x0
	
	
gdt_code:
	dw 0xffff    ;bits 0-15 
	dw 0x0       ;bits 16-31
	db 0x0       ;bits 32-39
	db 10011010b ;bits 40-47 defining p dpl s e ed/c r/w a respectively 
	db 11001111b ;bits 48 - 55 defining G d/b reserved avl segment len(4bits)
	db 0x0       ;last part of address bits       

gtd_data:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b ; p is present shows if it is available for use dpl shows privilage needed 0 is 
	db 11001111b ;highest only kernel level s is system of code/data segment 1 meaning its not a system seg
	db 0x0	     ;e is executable 0 meaning not executable 
		     ;ed/c is direction of growth ie is next entry on base +1 or base -1
		     ;rw is read write 1 is writable
		     ;a is whether this bit was accessed or not 
		     
		     
		     ;G is granularity how much is one block in the segment ie 1 means 1 block is 4kb 
		     ; d/b is protected mode
		     ;avl is if it is usable by hardware or not 
	 
	

gdt_end:

gdt_descriptor:
	dw gtd_end - gdt_start -1 
	dd gdt_start
	
CODE_SEG equ gdt_code-gdt_start
DATA_SEG equ gdt_data-gdt_start

