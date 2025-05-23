
#include "../gdt/gdt.h"

%macro ISR_NOERRCODE 1

    [GLOBAL isr%1]

    isr%1:
        cli 
        push byte   0 
        push byte   %1 
        jmp         isr_common_stub 

%endmacro 

%macro ISR_ERRCODE  1

    [GLOBAL isr%1]
    
    isr%1:
        cli 
        push    byte    0
        push    byte    %1
        jmp         isr_common_stub
%endmacro

%macro IRQ  2 
    [GLOBAL irq%1]
    irq%1:
        cli 
        push    byte 0 
        push    byte %2
        jmp     irq_common_stub 
%endmacro



ISR_NOERRCODE   0
ISR_NOERRCODE   1
ISR_NOERRCODE   2
ISR_NOERRCODE   3
ISR_NOERRCODE   4 
ISR_NOERRCODE   5
ISR_NOERRCODE   6
ISR_NOERRCODE   7
ISR_ERRCODE     8
ISR_NOERRCODE   9
ISR_ERRCODE     10
ISR_ERRCODE     11
ISR_ERRCODE     12
ISR_ERRCODE     13
ISR_ERRCODE     14
ISR_NOERRCODE   15
ISR_NOERRCODE   16
ISR_NOERRCODE   17
ISR_NOERRCODE   18
ISR_NOERRCODE   19
ISR_NOERRCODE   20
ISR_NOERRCODE   21
ISR_NOERRCODE   22
ISR_NOERRCODE   23
ISR_NOERRCODE   24
ISR_NOERRCODE   25
ISR_NOERRCODE   26
ISR_NOERRCODE   27
ISR_NOERRCODE   28
ISR_NOERRCODE   29
ISR_NOERRCODE   30
ISR_NOERRCODE   31

IRQ   0,    32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47


[GLOBAL syscall_intr]
syscall_intr:
    cli 
    push    byte 0 
    push    dword 0x0000080
    jmp     irq_common_stub 

[EXTERN isr_handler]

isr_common_stub:
    pusha       ;pushes edi, esi, ebp, esp, ebx, esx, ecx, eax 

    ;save userspace data segemnt descriptor
    mov     ax, ds 
    push    eax 

    ;transition to kernel data segemnt descripto 
    mov     ax, GDT_OFFSET_KERNEL_DATA  
    mov     ds, ax 
    mov     es, ax 
    mov     fs, ax 
    mov     gs, ax 

    ;create pointer to our registers 
    ;esp points at the top of the stack (last value pushed)
    ;pass current stack pointer(esp) as argument 
    ;interrupt funtion will interpret pointer as pointer to register structure 
    push    esp 
    call    isr_handler
    add     esp, 4 

    pop     eax     ;reoad original data segment descriptor 
    mov     ds, ax 
    mov     es, ax 
    mov     fs, ax 
    mov     gs, ax 

    popa 
    add     esp, 8
    sti 
    iret


[EXTERN irq_handler]

irq_common_stub:
    pusha           ;push registers 

    ;save current data segment 
    mov     ax, ds 
    push    eax

    ;load kernel segment selectors 
    
    mov     ax, GDT_OFFSET_KERNEL_DATA
    mov     ds, ax 
    mov     es, ax 
    mov     fs, ax 
    mov     gs, ax 

    push    esp 
    call    irq_handler 
    add     esp, 4 

    ;restore    old segment selectos 
    pop     ebx
    mov     es, bx 
    mov     es, bx 
    mov     fs, bx
    mov     gs, bx 

    ;restore common registers 
    popa
    
    ;remove ISR from stack 
    add     esp, 8 

    ;re-enbale interrupts 
    sti 
    iret 



