
#include "common.h"
#include "monitor.h"

int kmain(struct multiboot *mboot_ptr)
{
    monitor_clear();
    monitor_write("hello world\n");
    
    return 0xDEADBABA; 
}
