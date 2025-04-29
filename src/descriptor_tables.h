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

#endif // ! DESCRIPTOR_TABLES_H 
