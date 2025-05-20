#include "gdt.h"
#include "../../../lib/common.h"
#include "../../../lib/tinylib.h"

#define MAX_GDT_ENTRIES     5

extern gdt_load(uint32_t); 
extern gdt_flush(uint32_t); 

gdt_entry_t gdt_entries[MAX_GDT_ENTRIES]; 
gdt_ptr_t   gdt_ptr; 

static void gdt_set_entries(uint32_t entry_num, uint32_t base, uint32_t limit,
                     uint8_t access_byte, uint8_t granularity)
{
    gdt_entries[entry_num].base_low = (base & 0xFFFF); 
    gdt_entries[entry_num].base_middle = (base >> 16) & 0xFF; 
    gdt_entries[entry_num].base_high = (base >> 24) & 0xFF; 

    gdt_entries[entry_num].limit_low = (limit & 0xFFFF); 
    gdt_entries[entry_num].granularity = (limit >> 16) & 0x0F; 

    gdt_entries[entry_num].granularity |= granularity & 0xF0; 
    gdt_entries[entry_num].access_byte = access_byte; 
}

void init_gdt(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * MAX_GDT_ENTRIES);
    gdt_ptr.base  = &gdt_entries; 

    gdt_set_entries(0, 0, 0, 0, 0);
    /*kernel code */ 
    gdt_set_entries(1, 0, 0xFFFFFFFF, GDT_BASIC_DESCRIPTOR |
                    GDT_DESCRIPTOR_EXECUTABLE,
                    GDT_BASIC_GRANULARITY); 

    /*kernel data */
    gdt_set_entries(2, 0, 0xFFFFFFFF, GDT_BASIC_DESCRIPTOR,
                    GDT_BASIC_GRANULARITY); 

    /*user code */ 
    gdt_set_entries(3, 0, 0xFFFFFFFF, GDT_BASIC_DESCRIPTOR |
                    GDT_DESCRIPTOR_DPL |
                    GDT_DESCRIPTOR_EXECUTABLE,
                    GDT_BASIC_GRANULARITY); 
    /*user data */
    gdt_set_entries(4, 0xFFFFFFFF, GDT_BASIC_DESCRIPTOR |
                    GDT_DESCRIPTOR_DPL, 
                    GDT_BASIC_GRANULARITY);

    gdt_load((uint32_t)&gdt_ptr); 

}


