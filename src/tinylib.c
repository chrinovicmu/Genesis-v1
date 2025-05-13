
#include "common.h"
#include "tinylib.h"

void * memset(void *dst, int value, size_t size)
{
    uint8_t *temp = (uint8_t* )dst; 
    for(; size != 0; --size)
    {
        *temp++ = value; 
    }

}
