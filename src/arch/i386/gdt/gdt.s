
#include "gdt.h"

[GLOBAL gdt_load]

gdt_load:

    mov     eax, [esp+4]    ;get pointer of gdt passed as a parameter
    lgdt    [eax]

    mov     ax, GDT_OFFSET_KERNEL_DATA       ; offset in gdt to data segment 
    mov     ds, ax 
    mov     es, ax
    mov     fs, ax 
    mov     gs, ax 
    mov     ss, ax 
    jmp     GDT_OFFSET_KERNEL_CODE:.load    ;far jump to code segment 

.load:
    ret 

