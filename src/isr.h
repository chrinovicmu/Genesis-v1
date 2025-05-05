#ifndef ISR_H 
#define ISR_H

#include "common.h"

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
void register_interrput_handler(uint8_t, isr_t handler);

#endif 
