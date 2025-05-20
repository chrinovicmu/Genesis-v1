#ifndef IDT_H 
#define IDT_H 

#include "../../../lib/common.h"
#include "../gdt/gdt.h"

#define IDT_DESCRIPTOR_RING0                0x00
#define IDT_DESCRIPTOR_RING1                0x40 
#define IDT_DESCRIPTOR_RING2                0x20
#define IDT_DESCRIPTOR_RING3                0x80 

#define IDT_DESCRIPTOR_X16_GATE_TASK        0x05
#define IDT_DESCRIPTOR_X16_GATE_INTERRUPT   0x06 
#define IDT_DESCRIPTOR_X16_GATE_TRAP        0x07 
#define IDT_DESCRIPTOR_X32_GATE_TASK        0x0E 
#define IDT_DESCRIPTOR_X32_GATE_INTERRUPT   0x0F

#define IDT_DESCRIPTOR_PRESENT              0x80 

#define IDT_BASIC_DESCRIPTOR                (IDT_DESCRIPTOR_X32_GATE_INTERRUPT | IDT_DESCRIPTOR_PRESENT | IDT_DESCRIPTOR_RING0)
#define MAX_IDT_ENTRIES         256 
#define CPU_EXCEPTION_COUNT     32 

#define IDT_DESCRIPTOR_EXCEPTION            (IDT_DESCRIPTOR_X32_GATE_INTERRUPT | IDT_DESCRIPTOR_PRESENT)
#define IDT_DESCRIPTOR_EXTERNAL             (IDT_DESCRIPTOR_X32_GATE_INTERRUPT | IDT_DESCRIPTOR_PRESENT)
#define IDT_DESCRIPTOR_CALL                 (IDT_DESCRIPTOR_X32_GATE_INTERRUPT | IDT_DESCRIPTOR_PRESENT | IDT_DESCRIPTOR_RING3)

struct idt_entry_t 
{
    uint16_t    offset_low; 
    uint16_t    selector;
    uint8_t     always0; 
    uint8_t     attribute_flags; 
    uint16_t    offset_high; 
}__attribute__((packed)); 

typedef struct idt_entry_t idt_entry_t;

struct idt_ptr_t 
{
    uint16_t    limit; 
    uint32_t    base; 
}__attribute__ ((packed)); 

typedef struct idt_ptr_t idt_ptr_t; 

void init_idt(void);
#endif // !IDT_H 
#define IDT_H 


