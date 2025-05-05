
#include "common.h"
#include "isr.h"
#include "monitor.h"

isr_t intertupt_handlers[256]; 

void register_interrput_handler(uint8_t n , isr_t handler)
{
    intertupt_handlers[n] = handler; 
}

void isr_handler(registers_t regs)
{
    if(intertupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = intertupt_handlers[regs.int_no]; 
        handler(regs); 
    }
    else
    {
        terminal_write_string("unhandeld intertup : "); 
        terminal_write_dec(regs.int_no); 
        terminal_putchar('\n');

    }

}


