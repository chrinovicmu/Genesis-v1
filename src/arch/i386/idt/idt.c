
#include "../../../lib/common.h"
#include "../../../lib/tinylib.h"

#define MAX_IDT_ENTRIES         256 
#define CPU_EXCEPTION_COUNT     32 

extern void idt_load(uint32_t); 

static void init_idt(void); 





