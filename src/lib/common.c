
#include "common.h"

void outb(uint16_t port, uint8_t value)
{

    __asm__ volatile (
        "outb %b0, %w1" 
        :
        : "a"(value), "Nd"(port) : "memory"
    );
}

uint8_t inb(uint16_t port)
{
    uint8_t ret; 

    /*load port in dx register 
    * perform inb on . input one byte from dx register to al*
    * return al */

    __asm__ volatile(
        "inb %w1, %b0" 
        : "=a" (ret)
        : "dN" (port)
        : "memory"
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
