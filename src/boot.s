

MBOOT_PAGE_ALIGN   equ 1 << 0  ;load kernel modules on page boundary  
MBOOT_INFO         equ 1 << 1  ;Provide kernel with memory info 
MBOOT_HEADER_FLAGS equ MBOOT_PAGE_ALIGN | MBOOT_INFO 
MBOOT_HEADER_MAGIC equ 0x1BADB002 
MBOOT_CHECKSUM     equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)


section .multiboot
align  4
    dd     MBOOT_HEADER_MAGIC
    dd     MBOOT_HEADER_FLAGS
    dd     MBOOT_CHECKSUM

section .bss
align  16

stack_bottom:
    resb    16384 ;16kb 
stack_top: 

section .text
global _start:function 
extern kmain 

_start:

    mov     esp, stack_top

    call    kmain 

    cli 

.hang:
    hlt 
    jmp .hang  


section .note.GNU-stack noalloc noexec nowrite progbits  





