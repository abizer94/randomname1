[bits 16] 
switch_to_32:
	cli
	lgdt [gdt_descriptor]
	mov eax,cr0; these 3 instructions basically set lsb of cr0 to 1
	or eax,0x1
	mov cr0,eax
	jmp CODE_SEG:init_32bit
	
[bits 32]
init_32bit:
	mov ax,DATA_SEG
	mov ds,ax
	mov ss,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	
	mov ebp,0x90000
	mov esp,ebp
	
	call B_32Bit
	
