disk_l:
    
        pusha 
        
        mov si,dap_p
        mov dl,[BOOT_DRV]
        mov ah,0x42
        int 0x13
        jc disk_error
        popa
        ret
        
;        pusha
 ;       push dx
  ;      
   ;     mov ah,0x02
    ;    mov al,dh
     ;   mov cl,0x02
        
      ;  mov ch,0x00
       ; mov dh,0x00
        
       ; int 0x13
       ; jc disk_error
        
       ; pop dx
       ; cmp al,dh
        
       ; jne sectors_error
       ; popa
       ; ret
       
       
dap_p:
        db 0x10
        db 0x00
        dw 25
        dw 0x0000
        dw 0x0100
        dq (0xFE3)
        
        
disk_error:
        jmp disk_loop
        
sectors_error:
        jmp disk_loop
disk_loop:
        jmp $
        
