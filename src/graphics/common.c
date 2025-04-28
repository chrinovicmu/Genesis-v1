
#include "common.h"

void outb(uint16_t port, uint8_t value)
{

    asm volatile (
        "outb %1, %0" 
        :
        : "dN" (port), "a" (value)
    );
}

uint16_t inb(uint16_t port)
{
    uint16_t ret; 

    /*load port in dx register 
    * perform inb on . input one byte from dx register to al*
    * return al */

    asm volatile(
        "inb %1, %0" 
        : "=a" (ret)
        : "dN" (port)
    );

    return ret;
}
uint16_t inw(uint16_t port)
{
    uint16_t ret; 

    asm volatile (
        "inw %1, %0"
        : "=a" (ret) 
        : "dN" (port));

    return ret; 
}
