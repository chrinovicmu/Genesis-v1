#include "timer.h"
#include "arch/i386/isr.h"
#include "graphics/monitor.h"

uint32_t tick = 0; 

static void timer_callback(registers_t regs)
{
    ++tick; 
    terminal_write_string("Tick..");
    terminal_write_dec(tick); 
    terminal_write_string("\n"); 
}

void init_timer(uint32_t frequency)
{
    register_interrupt_handler(IRQ0, &timer_callback);

    uint32_t divisor = 1193180 / frequency;

    /*port 0x43 - PIT command register */ 
    /*0x3 - channel 0 , system channel 
      0x6 -   */
    outb(0x43, 0x36);

    uint8_t div_low = (uint8_t)(divisor & 0xFF); 
    uint8_t div_high = (uint8_t)(divisor >> 8) & 0xFF; 

    outb(0x40, div_low);
    outb(0x40, div_high);

}


