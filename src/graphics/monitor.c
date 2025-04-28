#include "monitor.h>"

static void move_cursor(void)
{
    uint16_t cursor_location = cursor_y * 80 + cursor_x; 

    /*tell vga we are settinhg the hight cursor bytes */ 
    outb(0x3D4, 14); 

    /*send the high curosr bytes */ 
    outb(0x3D5, cursor_location >> 8); 

    /*tell vga we are settinh low cursor bytes */ 
    outb(0x3D4, 15); 

    /*send the low cursor bytes*/
    outb(0x3D5, cursor_location);
}

static void scroll(void)
{
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F); 
    uint16_t blank = 0x20 | (attribute_byte << 8); 

    //if row 25 is the end , we need to scrool up 
    if(cursor_y >= 25)
    {
        int x; 
        for(x = 0 * 80; x < 24 * 80; x++)
        {
            video_memory[x] = video_memory[x + 80];
        }

        for(x = 24*80; x < 25*80; ++x)
        {
            video_memory[x] = blank;
        }
        cursor_y =  24; 
    }


}
