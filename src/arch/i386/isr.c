
#include "lib/common.h"
#include "arch/i386/isr.h"
#include "drivers/graphics/monitor.h"

isr_t intertupt_handlers[256]; 

void register_interrupt_handler(uint8_t n , isr_t handler)
{
    intertupt_handlers[n] = handler; 
}

void isr_handler(registers_t* regs)
{
    if(intertupt_handlers[regs->int_no] != 0)
    {
        isr_t handler = intertupt_handlers[regs->int_no]; 
        handler(*regs); 
    }
    else
    {
        terminal_write_string("unhandeld intertup : "); 
        terminal_write_dec(regs->int_no); 
        terminal_putchar('\n');

    }

}

void irq_handler(registers_t *regs)
{
    if(regs->int_no >= 40)
    {
        outb(0xA0, 0x20); 
    }
    outb(0x20, 0x20); 

    if(intertupt_handlers[regs->int_no] != 0)
    {
        isr_t handler = intertupt_handlers[regs->int_no];
        handler(*regs); 
    }
}


