MULTI_BOOT_PAGE_ALIGN   equ 1 << 0  ;load kernel modules on page boundary  
MULTI_BOOT_INFO         equ 1 << 1  ;Provide kernel with memory info 
MULTI_BOOT_HEADER_MAGIC equ 0xBADB002 

MULTI_BOOT_HEADER_FLAGS equ MULTI_BOOT_PAGE_ALIGN | MULTI_BOOT_INFO 

MULTI_BOOT_CHECKSUM     equ -(MULTI_BOOT_HEADER_MAGIC + MULTI_BOOT_HEADER_FLAGS)


[Bits 32]

[GLOBAL multiboot]
[EXTERN code]
[EXTERN bss]
[EXTERN end]


multiboot:
    dd MULTI_BOOT_HEADER_MAGIC
    
    dd MULTI_BOOT_HEADER_FLAGS 

    dd MULTI_BOOT_CHECKSUM 

    dd  multiboot   ;location 
    dd  code
    dd  bss 
    dd  end 
    dd  start   ; kernel entry point 

[GLOBAL start]
[EXTERN kmain]

start:

    push    ebx 

    cli 
    call kmain
    jmp $








