#ifndef ISR_H 
#define ISR_H

#include "lib/common.h"

#define ISR0    0
#define ISR1    1
#define ISR2    2
#define ISR3    3
#define ISR4    4
#define ISR5    5
#define ISR6    6
#define ISR7    7
#define ISR8    8
#define ISR9    9
#define ISR10   10
#define ISR11   11
#define ISR12   12
#define ISR13   13
#define ISR14   14
#define ISR15   15
#define ISR16   16
#define ISR17   17
#define ISR18   18
#define ISR19   19
#define ISR20   20
#define ISR21   21
#define ISR22   22
#define ISR23   23
#define ISR24   24
#define ISR25   25
#define ISR26   26
#define ISR27   27
#define ISR28   28
#define ISR29   29
#define ISR30   30
#define ISR31   31

#define IRQ0    32
#define IRQ1    33
#define IRQ2    34
#define IRQ3    35
#define IRQ4    36
#define IRQ5    37
#define IRQ6    38
#define IRQ7    39
#define IRQ8    40
#define IRQ9    41
#define IRQ10   42
#define IRQ11   43
#define IRQ12   44
#define IRQ13   45
#define IRQ14   46
#define IRQ15   47

struct registers
{
    /*data segment selector*/
    uint32_t    ds; 

    uint32_t    edi; 
    uint32_t    ebp; 
    uint32_t    esp; 
    uint32_t    ebx; 
    uint32_t    edx; 
    uint32_t    ecx;
    uint32_t    eax; 

    /*interrupt number */
    uint32_t    int_no;
    uint32_t    err_code;

    /*pushed ny the processor autmatically */ 
    uint32_t    eip; 
    uint32_t    cs;
    uint32_t    eflags; 
    uint32_t    useresp;
    uint32_t    ss; 
};
typedef struct registers registers_t; 

typedef void(*isr_t)(registers_t); 



void isr0( void );
void isr1( void );
void isr2( void );
void isr3( void );
void isr4( void );
void isr5( void );
void isr6( void );
void isr7( void );
void isr8( void );
void isr9( void );
void isr10( void );
void isr11( void );
void isr12( void );
void isr13( void );
void isr14( void );
void isr15( void );
void isr16( void );
void isr17( void );
void isr18( void );
void isr19( void );
void isr20( void );
void isr21( void );
void isr22( void );
void isr23( void );
void isr24( void );
void isr25( void );
void isr26( void );
void isr27( void );
void isr28( void );
void isr29( void );
void isr30( void );
void isr31( void );
void isr32( void );

void irq0( void );
void irq1( void );
void irq2( void );
void irq3( void );
void irq4( void );
void irq5( void );
void irq6( void );
void irq7( void );
void irq8( void );
void irq9( void );
void irq10( void );
void irq11( void );
void irq12( void );
void irq13( void );
void irq14( void );
void irq15( void );
#endif 
