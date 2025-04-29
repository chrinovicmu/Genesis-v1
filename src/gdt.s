
[GLOBAL gdt_flush]

gdt_flush:

    mov     eax, [esp+4]    ;get pointer of gdt passed as a parameter
    lgdt    [eax]

    mov     ax, 0x10        ; offset in gdt to data segment 
    mov     ds, ax 
    mov     es, ax
    mov     fs, ax 
    mov     gs, ax 
    mov     ss, ax 
    jmp     0x80:.flush     ;far jump to code segment 

.flush:
    ret 

