start:  
xor eax, eax  
xor ebx, ebx  
xor ecx, ecx  
xor edx, edx   ; 寄存器清零  

mov bl, 1  
add esp, string - start ; 调整esp指向字符串  
mov  ecx, esp  
mov  dl, 5  
mov al, 4  
int 0x80                ;write(1, "FUNC\n", 5)  

mov al, 1  
mov bl, 1  
dec bl  
int 0x80                ; exit(0)  

string:  
db "FUCK",0xa  
