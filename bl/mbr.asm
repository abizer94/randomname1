[bits 16]
[org 0x7c00]

_start:
K_OFFSET equ 0x1000
mov [BOOT_DRV],dl

mov bp,0x9000
mov sp,bp

call find_k
call switch_to_32

jmp $

%include "bl/d.asm"
%include "bl/gdt.asm"
%include "bl/switch_to_32.asm"

[bits 16]

find_k:
        mov si, 0x7c00 + 0x1be; location of partition table1
        mov cx,4 ; 4 entries max
        cmp byte [si],0x80 ; is the partition bootable
        je load_k
        add si,16
        loop find_k
        jmp $
        
load_k: 
        mov eax,[si+8]
        add eax,0x01
        mov dl,[BOOT_DRV]
        call disk_l
        ret
        
        
[bits 32]
B_32Bit:
        ;call K_OFFSET
        call 0x1000
        jmp $
        
BOOT_DRV db 0
times 510 - ($-$$) db 0

dw 0xaa55 ; magic bytes to show that this is the mbr will actually write 55aa
          ; in memory 
          
          

