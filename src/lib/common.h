#ifndef COMMON_H 
#define COMMON_H

typedef unsigned int uint32_t;
typedef unsigned int size_t; 
typedef int int32_t; 
typedef unsigned short uint16_t;
typedef short int16_t; 
typedef unsigned char uint8_t; 
typedef char int8_t; 

static inline void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile
    (
        "outb %b0, %w1" 
        :
        : "a"(value), "Nd"(port)
        : "memory"
    ); 
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret; 

    __asm__ volatile 
    (
        "inb %w1, %b0"
        : "=a" (ret)
        : "Nd"(port)
        :"memory"
    );
}
static inline uint16_t inw(uint16_t port)
{
    uint16_t ret; 

    asm volatile (
        "inw %1, %0"
        : "=a" (ret) 
        : "dN" (port));
}

static inline void io_wait()
{
    outb(0x80, 0);
}
#endif 
