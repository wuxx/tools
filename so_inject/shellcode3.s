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

/* print some string to stdout */
.section .text
.globl _start
_start:
    push   $0x000a216f
    push   $0x6c6c6568  /* hello! */
    mov    %esp, %ecx

    mov    $0x8,%edx        /* count */
    /* mov    $0x80490a0,%ecx */  /* buf */
    mov    $0x1,%ebx        /* stdout */
    mov    $SYS_WRITE, %eax        
    int    $0x80
    
    mov    $0x0,%ebx        /* exit value */
    mov    $SYS_EXIT,%eax
    int    $0x80
