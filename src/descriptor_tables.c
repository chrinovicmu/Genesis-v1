#include "common.h"
#include "descriptor_tables.h"

#define MAX_GDT_ENTRIES 5  
#define MAX_IDT_ENTRIES 256 

extern void gdt_load(uint32_t); 
extern void idt_load(uint32_t); 

static void init_gdt(); 
static void init_idt(); 

static void gdt_set_gate(int32_t,uint32_t, uint32_t, uint8_t, uint8_t);
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

gdt_entry_t gdt_entries[MAX_GDT_ENTRIES]; 
idt_entry_t idt_entries[256];

gdt_ptr_t gdt_ptr;
idt_ptr_t   idt_ptr; 

void init_descriptor_tables(void)
{
    init_gdt();
    init_idt();
};

static void init_gdt(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t)*MAX_GDT_ENTRIES);
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                 /*Null segement */              
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);  /*Code segement */ 
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);  /*Data segement */ 
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);  /*User mode code segement */ 
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);  /*User mode data segement */ 

    gdt_load((uint32_t)&gdt_ptr); 
}

static void init_idt(void)
{

    idt_ptr.limit = sizeof(idt_entry_t) * (MAX_IDT_ENTRIES - 1);
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t)*MAX_IDT_ENTRIES);

    /*remap the irq table*/

    /*ICW1*/ 
    outb(0x20, 0x11);
    outb(0xA0, 0x11); 

    /*ICW2 */ 
    outb(0x21, 0x20); /*irq 0-7 */ 
    outb(0xA1, 0x28); /*urp 8-15 */ 

    /*ICW3 */ 
    outb(0x21, 0x04); /*irq line 2 - 0x0100-connecting to slave */ 
    outb(0xA1, 0x02); /*irq line 2 - bin(2)= 0x02 */ 

    /*ICW4 */
    /*80x86 mode */ 
    outb(0x21, 01); 
    outb(0xA1, 01);

    /*OCW */
    outb(0x21, 0x0);
    outb(0x21, 0x0); 

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
    idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
    idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
    idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
    idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
    idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
    idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);


    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);  // IRQ0 - Timer
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);  // IRQ1 - Keyboard
    idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);  // IRQ2 - Cascade for the slave PIC
    idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);  // IRQ3 - Serial port 2
    idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);  // IRQ4 - Serial port 1
    idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);  // IRQ5 - Parallel port 2 / Sound card
    idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);  // IRQ6 - Floppy disk controller
    idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);  // IRQ7 - Parallel port 1
    idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);  // IRQ8 - Real-time clock
    idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);  // IRQ9 - Free for expansion (used by network cards)
    idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E); // IRQ10 - Free for expansion
    idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E); // IRQ11 - Free for expansion
    idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E); // IRQ12 - PS/2 Mouse
    idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E); // IRQ13 - FPU (Floating point unit) exception
    idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E); // IRQ14 - Hard disk drive
    idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E); // IRQ15 - CD-ROM / SCSI
  
    idt_load((uint32_t)&idt_ptr); 
}

static void gdt_set_gate(int32_t entry_num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt_entries[entry_num].base_low = (base & 0xFFFF);
    gdt_entries[entry_num].base_middle = (base >> 16) & 0xFF; 
    gdt_entries[entry_num].base_high = (base >> 24) & 0xFF; 

    gdt_entries[entry_num].limit_low = (limit & 0xFFFF); 
    gdt_entries[entry_num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[entry_num].granularity |= granularity & 0xF0; 
    gdt_entries[entry_num].access = access; 
}

static void idt_set_gate(uint8_t entry_num, uint32_t offset, uint16_t selector, uint8_t atrribute_flags)
{
    idt_entries[entry_num].offset_low = offset & 0xFFFF; 
    idt_entries[entry_num].offset_high = (offset >> 16) &0xFFFF; 
    idt_entries[entry_num].selector = selector; 
    idt_entries[entry_num].always0 = 0; 

    /*OR mu be uncommented when we arive in user mode 
     * dpl changes to rin level 3*/
    idt_entries[entry_num].attribute_flags = atrribute_flags | 0x60;

}

