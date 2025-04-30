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
}

static void init_gdt(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t)*MAX_GDT_ENTRIES);
    gdt_ptr.base = (uint32_t)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                /*Null segmnet */ 
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /*Code segment */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /*Data segment */
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); /*User mode code segment */ 
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); /*User mode data segment */  

    gdt_load((uint32_t)&gdt_ptr); 
}

static void init_idt(void)
{
    idt_ptr.limit = sizeof(idt_entry_t) * (MAX_IDT_ENTRIES - 1);
    idt_ptr.base = (uint32_t)&idt_entries;

    memset(&idt_entries, 0, sizeof(idt_entry_t)*MAX_IDT_ENTRIES);

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E); 

    idt_set_gate(31, (uint32_t)isr32, 0x08, 0x8E);

    idt_load((uint32_t)&idt_ptr); 

}
/*set value of one gdt entry in memory */ 
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


/*set value for single idt entry */ 

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

