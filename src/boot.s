MULTI_BOOT_PAGE_ALIGN   equ 1 << 0  ;load kernel modules on page boundary  
MULTI_BOOT_INFO         equ 1 << 1  ;Provide kernel with memory info 
MULTI_BOOT_HEADER_MAGIC equ 0xBADB002 

MULTI_BOOT_HEADER_FLAGS equ MULTI_BOOT_PAGE_ALIGN | MULTI_BOOT_INFO 

MULTI_BOOT_CHECKSUM     equ -(MULTI_BOOT_HEADER_MAGIC + MULTI_BOOT_HEADER_FLAGS)


section .multiboot
    align  4
    dd     MULTI_BOOT_HEADER_MAGIC
    dd     MULTI_BOOT_HEADER_FLAGS
    dd     MULTI_BOOT_CHECKSUM

[Extern kmain]
[GLOBAL start]

section .bss
    align  16

    stack_bottom:
    resb    16384 ;16kb 
    stack_top: 

section .text
    global _start

    _start:


start:

    mov     esp, stack_top

    call    kmain 

    cli 
    hlt 
    jmp 1b 








