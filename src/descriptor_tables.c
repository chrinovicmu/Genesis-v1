#include "common.h"
#include "descriptor_tables.h"

#define MAX_GDT_ENTRIES 5  

extern void gdt_flush(uint32_t); 

static void init_gdt(); 
static void gdt_set_gate(int32_t,uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt_entries[MAX_GDT_ENTRIES];  
gdt_ptr_t gdt_ptr;
idt_entry_t idt_entries[256]; 
idr_ptr_t   idt_ptr; 

void init_descriptor_tables(void)
{
    init_gdt();

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





