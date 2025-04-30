#ifndef  DESCRIPTOR_TABLES_H 
#define DESCRIPTOR_TABLES_H

#include "common.h"
/*GDT entry*/ 

struct gdt_entry
{
    uint16_t    limit_low; 
    uint16_t    base_low; 
    uint8_t     base_middle;
    uint8_t     access; 
    uint8_t     granularity; 
    uint8_t     base_high; 
}__attribute__((packed)); 

typedef struct gdt_entry gdt_entry_t; 

struct gdt_ptr
{
    uint16_t limit; 
    uint32_t base; 
}__attribute__((packed));

typedef struct gdt_ptr gdt_ptr_t; 

void init_descriptor_tables(void);

struct idt_entry
{
    uint16_t    offset_low;   /*lower 16 bits of address to jump to when interupt fires */
    uint16_t    selector; 
    uint8_t     always0; 
    uint8_t     attribute_flags; 
    uint16_t    offset_high; 
}__attribute__((packed)); 

typedef struct idt_entry idt_entry_t; 

struct idt_ptr
{
    uint16_t    limit; 
    uint32_t    base;
}__attribute__((packed)); 

typedef struct idt_ptr idt_ptr_t; 

extern void isr0(void);
extern void isr31(void); 


#endif // ! DESCRIPTOR_TABLES_H 
