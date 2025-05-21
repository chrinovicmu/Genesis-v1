#ifndef GDT_H 
#define GDT_H

#include "lib/common.h"

#define GDT_MAX_DESCRIPTORS         0x2000 
#define GDT_DESCRIPTOR_SIZE         0x08 

#define GDT_DESCRIPTOR_ACCESS       0x01
#define GDT_DESCRIPTOR_RW           0x02 

/*execute code without change of ring level 
 * data segement grows downward */
#define GDT_DESCRIPTOR_DC           0x04 
#define GDT_DESCRIPTOR_EXECUTABLE   0x08 

/*code and data segment type */ 
#define GDT_DESCRIPTOR_TYPE_C_D     0x10 

#define GDT_DESCRIPTOR_DPL          0x60 
#define GDT_DESCRIPTOR_P            0x80 

#define GDT_GRANUALITY_OS           0x10  
#define GDT_GRANUALITY_X64          0x20 
#define GDT_GRANUALITY_X32          0x40 
#define GDT_GRANUALITY_4K           0x80 

#define GDT_OFFSET_KERNEL_CODE      (0x01 * 0x08)
#define GDT_OFFSET_KERNEL_DATA      (0x02 * 0x08)
#define GDT_OFFSET_USER_CODE        (0x03 * 0x08)
#define GDT_OFFSET_USER_DATA        (0x04 * 0x08)


#define GDT_BASIC_DESCRIPTOR        (GDT_DESCRIPTOR_P | GDT_DESCRIPTOR_RW | GDT_DESCRIPTOR_TYPE_C_D)
#define GDT_BASIC_GRANULARITY       (GDT_GRANUALITY_X32 | GDT_GRANUALITY_4K)

struct gdt_entry  
{
    uint16_t    limit_low; 
    uint16_t    base_low; 
    uint8_t     base_middle; 
    uint8_t     access_byte; ;
    uint8_t     granularity; 
    uint8_t     base_high; 
}__attribute__((packed)); 

typedef struct gdt_entry gdt_entry_t; 

void init_gdt(void);

struct gdt_ptr
{
    uint16_t    limit;  /*size of gdt */ 
    uint32_t    base;   /*address of gdt */  
}__attribute__ ((packed)); 

typedef struct gdt_ptr gdt_ptr_t;
#endif // !GDT_H 
