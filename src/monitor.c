#include "common.h"
#include "monitor.h"

uint32_t terminal_row; 
uint32_t terminal_column; 
uint8_t terminal_color; 
uint16_t * terminal_buffer = (uint16_t*)VGA_MEMORY;

size_t strlen(const char *str)
{
    size_t len = 0; 
    while(str[len]){
        len++;
    }
    return len;
}

void terminal_initialize(void)
{
    terminal_row = 0; 
    terminal_column = 0; 
    terminal_color = vga_attribute_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK); 

    for(size_t y = 0; y < VGA_HEIGHT; ++y)
    {
        for (size_t x = 0; x < VGA_WIDTH; ++x)
        {
            const size_t index = y * VGA_WIDTH +x;
            terminal_buffer[index] = vga_attribute(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color; 
}


void terminal_putentryat(char c , uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_attribute(c, color); 
}

void terminal_putchar(char c)
{
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row); 
    if(++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0; 
        if(++terminal_row == VGA_HEIGHT)
        {
            terminal_row = 0; 
        }
    }
}

void terminal_write(const char *data, size_t size)
{
    for(size_t x =0; x < size; ++x)
    {
        terminal_putchar(data[x]);
    }
}
void terminal_write_string(const char* data)
{
    terminal_write(data, strlen(data)); 
}

void terminal_write_dec(uint32_t n)
{
    if(n == 0)
    {
        terminal_putchar('0');
        return;
    }
    int32_t acc = n ; 
    char c[32]; 
    int x = 0;

    while(acc > 0)
    {
        c[x] = '0' + (acc % 10); 
        acc /= 10; 
        ++x; 
    }
    c[x] = '\0'; 

    char c2[32]; 
    c2[--x] = '\0'; 
    int j = 0; 

    while (x >= 0)
    {
        c2[--x] = c[j++];
    }

    terminal_write_string(c2);

}
