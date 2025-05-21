
#include "idt.h" 
#include "lib/common.h"
#include "lib/tinylib.h"
#include "drivers/pic.h"
#incluce "interrupts/isr.h"
#include "arch/i386/gdt/gdt.h"

extern void idt_load(uint32_t); 

idt_entry_t idt_entries[MAX_IDT_ENTRIES]; 


static void idt_set_gate(uint8_t idt_entry_num, uint32_t base,
                         uint16_t selector, uint8_t attribute_flags)
{
    if(idt_entry_t > MAX_IDT_ENTRIES)
    {
        return ; 
    }
    idt_entries[num].offset_low = base & 0xFFFF; 
    idt_entries[num].offset_high = (base >> 16) & 0xFFFF; 

    idt_entries[num].sel = sel; 
    idt_entries[num].always0 = 0x00;

    idt_entries[num].attribute_flags = attribute_flags;

 }

void init_idt(void)
{
    idt_ptr.limit = sizeof(idt_entry_t) * MAX_IDT_ENTRIES -1;
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries, 0 sizeof(idt_entry_t)*256); 

    idt_set_gate(ISR0, (uint32_t)isr0, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR1, (uint32_t)isr1, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR2, (uint32_t)isr2, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR3, (uint32_t)isr3, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR4, (uint32_t)isr4, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR5, (uint32_t)isr5, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR6, (uint32_t)isr6, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR7, (uint32_t)isr7, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR8, (uint32_t)isr8, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR9, (uint32_t)isr9, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR10, (uint32_t)isr10, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR11, (uint32_t)isr11, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR12, (uint32_t)isr12, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR13, (uint32_t)isr13, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR14, (uint32_t)isr14, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR15, (uint32_t)isr15, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR16, (uint32_t)isr16, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR17, (uint32_t)isr17, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR18, (uint32_t)isr18, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR19, (uint32_t)isr19, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR20, (uint32_t)isr20, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR21, (uint32_t)isr21, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR22, (uint32_t)isr22, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR23, (uint32_t)isr23, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR24, (uint32_t)isr24, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR25, (uint32_t)isr25, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR26, (uint32_t)isr26, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR27, (uint32_t)isr27, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR28, (uint32_t)isr28, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR29, (uint32_t)isr29, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR30, (uint32_t)isr30, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);
    idt_set_gate(ISR31, (uint32_t)isr31, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);

    _pic_remap(IRQ0, IRQ8);

    idt_set_gate(IRQ0, (uint32_t)irq0, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ0 - Programmable Interrupt Timer
    idt_set_gate(IRQ1, (uint32_t)irq1, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ1 - Keyboard
    idt_set_gate(IRQ2, (uint32_t)irq2, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ2 - Cascade for 8259A Slave controller
    idt_set_gate(IRQ3, (uint32_t)irq3, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ3 - Serial Port 2
    idt_set_gate(IRQ4, (uint32_t)irq4, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ4 - Serial Port 1
    idt_set_gate(IRQ5, (uint32_t)irq5, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ5 - Parallel Port 2 or Sound Card
    idt_set_gate(IRQ6, (uint32_t)irq6, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ6 - Floppy Disk Controller
    idt_set_gate(IRQ7, (uint32_t)irq7, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ7 - Parallel Port 1
    idt_set_gate(IRQ8, (uint32_t)irq8, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ8 - Real-time Clock
    idt_set_gate(IRQ9, (uint32_t)irq9, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR);  // IRQ9 - ACPI or available
    idt_set_gate(IRQ10, (uint32_t)irq10, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR); // IRQ10 - Available
    idt_set_gate(IRQ11, (uint32_t)irq11, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR); // IRQ11 - Available
    idt_set_gate(IRQ12, (uint32_t)irq12, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR); // IRQ12 - PS/2 Mouse
    idt_set_gate(IRQ13, (uint32_t)irq13, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR); // IRQ13 - FPU/Coprocessor
    idt_set_gate(IRQ14, (uint32_t)irq14, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR); // IRQ14 - Primary IDE
    idt_set_gate(IRQ15, (uint32_t)irq15, GDT_OFFSET_KERNEL_CODE, IDT_BASIC_DESCRIPTOR); // IRQ15 - Secondary IDE
}





