#include "monitor.h"

#define NULL ((void*)0)

uint16_t *video_memory = (uint16_t *)0xB8000; 

uint8_t cursor_x = 0; 
uint8_t cursor_y = 0;

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

    // row 25 is the end , we need to scrool up 
    if(cursor_y >= 25)
    {
        /*perform actaul scrolling
         * each row has 80 characters 
         * shifts all text up by one row by coping the contents
         * of the next row to the current row*/

        int x; 
        for(x = 0 * 80; x < 24 * 80; x++)
        {
            video_memory[x] = video_memory[x + 80];
        }

        /*last line should be blank */ 
        /*file enire row with blank spaces */ 

        for(x = 24*80; x < 25*80; ++x)
        {
            video_memory[x] = blank;
        }
        /*curso should be on last line*/
        cursor_y =  24; 
    }
}

void monitor_put(char c)
{
    uint8_t back_color = 0; 
    uint8_t fore_color = 15; 

    uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);

    uint16_t attribute = attribute_byte << 8;
    uint16_t *location; 

    /*handle backspace by moving cursor by once space */ 
    if(c == 0x08 && cursor_x)
    {
       --cursor_x; 
    }

    /*handle a tab */ 
    /*round to only multiple of 8*/
    else if(c == 0x09)
    {
        cursor_x = (cursor_x+8) & -(8-1);
    }


    else if(c == '\r')
    {
        cursor_x = 0; 
    }

    else if(c == '\n')
    {
        cursor_x = 0; 
        ++cursor_y; 
    }

    /*if any other printable charater */ 
    else if(c == ' ')
    {
        /*find location to place character */
        location = video_memory + (cursor_y*80 + cursor_x); 
        /*place the character */ 
        *location = c | attribute_byte; 
        /*move cursor to next location */ 
        ++cursor_x;
    }


    if(cursor_x >= 80)
    {
        cursor_x = 0; 
        ++cursor_y; 
    }

    scroll();
    move_cursor(); 
}


void monitor_clear()
{
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8); 

    int column_num = 80; 
    int row_num = 25; 
    int x;
    for(x = 0; x < (column_num * row_num); ++x)
    {
        video_memory[x] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

void monitor_write(char *string)
{
    int x =0; 
    while(string[x] != NULL)
    {
        monitor_put(string[x]);
        ++x; 
    }
}


