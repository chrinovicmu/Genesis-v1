

#include "common.h"
#include "monitor.h"
#include "multiboot.h"
#include "timer.h"
#include "descriptor_tables.h"



int kmain(struct mboot_info *mboot_ptr)
{
    terminal_initialize();
    terminal_write_string("HELLO WORLD from my kernel\n");
    terminal_write_string("Im chrinoviuc "); 
  
    init_descriptor_tables(); 
    init_timer(50);
}
