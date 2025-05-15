

#include "../lib/common.h"
#include "../drivers/graphics/monitor.h"
#include "../include/multiboot.h"
#include "../drivers/timer/timer.h"
#include "../arch/i386/descriptor_tables.h"
#include "../lib/tinylib.h"


int kmain(struct mboot_info *mboot_ptr)
{
    terminal_initialize();
    terminal_write_string("HELLO WORLD from my kernel\n");
    terminal_write_string("Im chrinoviuc "); 
  
    init_descriptor_tables(); 
    init_timer(50);
}
