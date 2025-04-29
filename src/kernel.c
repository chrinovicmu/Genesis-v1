

#include "common.h"
#include "monitor.h"
#include "multiboot.h"


int kmain(struct mboot_info *mboot_ptr)
{
    monitor_clear();
    monitor_write("hello world\n");
    
    return 0x1BADB002; 
}
