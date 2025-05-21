#ifndef MONITOR_H 
#define MONITOR_H 

#include "lib/common.h"

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000 

extern uint32_t    terminal_row;
extern uint32_t    terminal_column; 
extern uint8_t     terminal_color;
extern uint16_t *  terminal_buffer;

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};


static inline uint8_t vga_attribute_color(enum vga_color fg, enum vga_color bg)
{
    uint8_t colors = 0;
    colors |= fg; 
    colors |= (bg << 0x0F) << 4; 

    return colors;
}

static inline uint16_t vga_attribute(unsigned char uc , uint8_t colors)
{
    uint16_t attributes = 0; 
    attributes |= uc;
    attributes |=(uint16_t)colors << 8; 

    return attributes; 
}
size_t strlen(const char* str); 

void terminal_initialize(void);
void terminal_setcolor(uint8_t color); 
void terminal_putentryat(char c , uint8_t color, uint32_t x , uint32_t y); 
void terminal_putchar(char c); 
void terminal_write(const char * data, uint32_t size); 
void terminal_write_string(const char * data); 
void terminal_write_dec(uint32_t n); 
#endif // !MONITOR_H 



