#system call numbers
.equ SYS_OPEN, 5
.equ SYS_WRITE, 4
.equ SYS_READ, 3
.equ SYS_CLOSE, 6
.equ SYS_EXIT, 1

.equ STDIN, 0
.equ STDOUT, 1
.equ STDERR, 2

.equ O_RDONLY, 0x0
.equ O_WRONLY, 0x1
.equ O_RDWR,   0x2
.equ O_CREAT_WRONLY_TRUNC, 03101

/* write data to file */
.section .text
.globl _start

/*  
pusha
Temp <- (ESP); 
Push(EAX); 
Push(ECX); 
Push(EDX); 
Push(EBX); 
Push(Temp); 
Push(EBP); 
Push(ESI); 
Push(EDI); 

popa

*/
_start:
    pusha
    call   get_eip          /* eax point to next instruction start addr */
    add    $9, %eax
    call   sub_func1
    popa

    mov    $0x0,%ebx        /* exit value */
    mov    $SYS_EXIT,%eax
    int    $0x80

    /* get eip in eax */
get_eip:
    mov (%esp), %eax
    ret

sub_func1:
    mov  %esp, %esi

    push $0x0000302f
    push $0x7374702f
    push $0x7665642f    /* /dev/pts/0 */
    mov  %esp, %eax

    push $0x000a216f
    push $0x6c6c6568  /* hello! */
    mov  %esp, %ebx

    push %eax
    push %ebx
    mov  %esp, %ebp

    /* open */
    mov 4(%ebp), %ebx      /* filename in ebp[0] */
    mov $O_RDWR, %ecx   /* open mode */
    mov $0666, %edx     /* attribute */

    mov $SYS_OPEN, %eax
    int $0x80   /* return fd in eax */

    /* write */
    mov $0x8, %edx        /* count */
    mov 0(%ebp), %ecx     /* buf */
    mov %eax, %ebx        /* fd */

    mov $SYS_WRITE, %eax        
    int $0x80

    /* close */
    mov %ebx, %ebx
    mov $SYS_CLOSE, %eax
    int $0x80

    mov %esi, %esp
    ret
    

