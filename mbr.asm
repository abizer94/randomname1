[bits 16]
[org 0x7c00]

K_OFFSET equ 0x1000
mov [BOOT_DRV],dl

mov bp,0x9000
mov sp,bp

call load_k
call switch_to_32

jmp $

%include "d.asm"
%include "gdt.asm"
%include "switch_to_32.asm"

[bits 16]
load_k:
        mov bx,K_OFFSET
        mov dh,2
        mov dl,[BOOT_DRV]
        call disk_l
        ret
[bits 32]
B_32Bit:
        call K_OFFSET
        jmp $
        
BOOT_DRIVE db 0
times 510 - ($-$$) db 0

dw 0xaa55 ; magic bytes to show that this is the mbr will actually write 55aa
          ; in memory 
          
          

