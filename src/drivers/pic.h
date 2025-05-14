#ifndef PIC_H 
#define PIC_H 

#include "lib/common.h"

#define PIC_1_COMMAND   0x20
#define PIC_2_COMMAND   0xA0
#define PIC_1_DATA      0x21 
#define PIC_2_DATA      0xA1

#define PIC_EOI         0x20 

void PIC_sendEOI(uint8_t irq)
{
    /*if irq came from master , issue EIO to master only */ 
    /*if irq came from slave (irq => 8), issue to both */ 
    if(irq >= 8)
    {
        outb(PIC_2_COMMAND, PIC_EOI);
    }
    outb(PIC_1_COMMAND, PIC_EOI); /*always issue to master */  
}



#endif // !PIC_H 
#define PIC_H 
I
