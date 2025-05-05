

#include "common.h"
#include "monitor.h"
#include "multiboot.h"


int kmain(struct mboot_info *mboot_ptr)
{
    terminal_initialize();
    terminal_write_string("HELLO WORLD from my kernel\n");
    terminal_write_string("Im chrinoviuc "); 
    
}
