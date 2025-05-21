
#include "lib/common.h"
#include "isr.h"
#include "drivers/graphics/monitor.h"
#include "drivers/pic.h"

isr_t intertupt_handlers[256];

/*
cosnt char * g_fault_names[] = {
    "Divide-by-Zero Error",
	"Debug",
	"Non-Maskable Interrupt",
	"Breakpoint",
	"Overflow",
	"Bound Range Exceeded",
	"Invalid Opcode",
	"Device Not Available",
	"Double Fault",
	"Coprocessor Segment Overrun",
	"Invalid TSS",
	"Segment Not Present",
	"Stack-Segment Fault",
	"General Protection Fault",
	"Page Fault",
	"Reserved",
	"x87 Floating-Point Exception",
	"Alignment Check",
	"Machine Check",
	"SIMD Floating-Point Exception",
	"Virtualization Exception",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Security Exception",
	"Reserved"
}; 
*/ 
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
    uint8_t irq = regs->int_no - 32; 

    pic_sendEOI(irq); 

    if(intertupt_handlers[regs->int_no] != 0)
    {
        isr_t handler = intertupt_handlers[regs->int_no];
        handler(*regs); 
    }
}


