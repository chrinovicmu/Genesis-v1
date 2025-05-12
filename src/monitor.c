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
    // Special case: handle zero explicitly
    if (n == 0)
    {
        terminal_putchar('0');
        return;
    }

    // Buffer to store extracted digits (in reverse order)
    char digit_buffer[32]; 
    
    // Index to track current position in digit_buffer
    int buffer_index = 0;

    // Local copy of input to avoid modifying original
    uint32_t current_number = n;

    // Extract digits from least significant to most significant
    while (current_number > 0)
    {
        // Convert digit to character and store in buffer
        // Use '0' + remainder to convert numeric digit to character
        digit_buffer[buffer_index++] = '0' + (current_number % 10);
        
        // Integer division to move to next digit
        current_number /= 10;
    }

    // Null-terminate the buffer for safety
    digit_buffer[buffer_index] = '\0';

    // Reversed string buffer
    char reversed_buffer[32];
    
    // Reverse the digits to correct order
    int reversed_index = 0;
    while (buffer_index > 0)
    {
        // Copy digits from end of original buffer to start of reversed buffer
        reversed_buffer[reversed_index++] = digit_buffer[--buffer_index];
    }

    // Null-terminate the reversed buffer
    reversed_buffer[reversed_index] = '\0';

    // Write the reversed (now correct order) string to terminal
    terminal_write_string(reversed_buffer);
}
