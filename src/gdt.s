
[GLOBAL gdt_load]

gdt_load:

    mov     eax, [esp+4]    ;get pointer of gdt passed as a parameter
    lgdt    [eax]

    mov     ax, 0x10        ; offset in gdt to data segment 
    mov     ds, ax 
    mov     es, ax
    mov     fs, ax 
    mov     gs, ax 
    mov     ss, ax 
    jmp     0x08:.load    ;far jump to code segment 

.load:
    ret 

[GLOBAL idt_load]

idt_load:
    mov eax, [esp+4]
    lidt    [eax]
    ret 
