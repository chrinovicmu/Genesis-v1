#ifndef PIC_H 
#define PIC_H 

#include "../lib/common.h"

#define PIC_1_COMMAND   0x20
#define PIC_2_COMMAND   0xA0
#define PIC_1_DATA      0x21 
#define PIC_2_DATA      0xA1

#define PIC_EOI         0x20    

#define ICW1_ICW4       0x01    /*indicate that ICW4 id present */ 
#define ICW1_SINGLE     0x02    /* single cascade mode */ 
#define ICW1_INTERVAL4  0x04    /*vall address interval 4 */ 
#define ICW1_LEVEL      0x80    /*level triggers (edge mod) */  
#define ICW1_INIT       0x10    /*initialization */ 

#define ICW4_8068       0x01    /*bit 0 8086 mode */ 
#define ICW4_AUTO       0x02    /*bit 1 enable automatic EIO*/ 
#define ICW4_BUF_SLAVE  0x08    /*bit 3 set and bit 2 cleared  buffered mode */ 
#define ICW4_BUF_MASTER 0x0C    /*both 3 & 2 set buffered mode */ 
#define ICW4_SFNM       0x10    /*bit 4 sfnm enabled -interupt priorities*/ 

#define PIC_READ_IRR    0x0A    
#define PIC_READ_ISR    0x0B 


void PIC_sendEOI(uint8_t irq)
{
    /*if irq came from master , issue EIO to master only */ 
    /*if irq came from slave (irq => 8), issue to both */ 
    if(irq >= 8)
    {
        outb(PIC_2_COMMAND, PIC_EOI);
    }    outb(PIC_1_COMMAND, PIC_EOI); /*always issue to master */  
}

void PIC_remap(int offset1, int offset2)
{
    //init initialization sequence (cascade mode )
    outb(PIC_1_COMMAND, ICW1_INIT | ICW1_ICW4); 

    /*slave initialization*/ 
    io_wait(); 
    outb(PIC_2_COMMAND, ICW1_INIT | ICW1_ICW4); 

    /*offset of pic m=32-40(0x20) s=40-427(0x28) */ 
    io_wait();
    outb(PIC_1_DATA, offset1);
    io_wait();
    outb(PIC_2_DATA, offset2); 

    /*----CASCADE MODE CONFIG-- */ 

    /*for cascading- connect to irq line 2 */
    io_wait();
    outb(PIC_1_DATA, 0x04);

    /*tell slave master irq2 value in bin*/
    io_wait(); 
    outb(PIC_2_DATA, 0x02); 


    /*----ICW4 CONFIG----*/ 
    io_wait();
    outb(PIC_1_DATA, ICW4_8068); 
    io_wait(); 
    outb(PIC_1_DATA, ICW4_8068); 

    /*unmask both PICs */ 
    outb(PIC_1_DATA, 0);
    outb(PIC_2_DATA, 0);
}

void pic_disable(void)
{
    outb(PIC_1_DATA, 0xFF);
    outb(PIC_2_DATA, 0xFF); 
}

void IRQ_set_mask(uint8_t IRQ_line)
{
    uint16_t port; 
    uint8_t value; 

    if(IRQ_line < 8){
        port = PIC_1_DATA; 
    }else{
        port = PIC_2_DATA; 
        IRQ_line -= 8; 
    }
    /*mask current value of IMR with mask value */ 
    value = inb(port) | ( 1 << IRQ_line);
    outb(port, value);
}

void IRQ_clear_mask(uint8_t IRQ_line)
{
    uint16_t port;
    uint8_t value; 

    if(IRQ_line < 8){
        port = PIC_1_DATA;
    }else{
        port = PIC_2_DATA;
        IRQ_line -= 8;
    }
    value = inb(port) & ~(1 << IRQ_line);
    outb(port, value);
}
static uint16_t __pic_get_irq_reg(int ocw_3)
{
    /*make irr and isr readable */ 
    outb(PIC_1_COMMAND, ocw_3);
    outb(PIC_2_COMMAND, ocw_3);

    /*read master and slace pic */
    return (inb(PIC_2_COMMAND) << 8) | (inb(PIC_1_COMMAND)); 

}

uint16_t __pic_get_IRR(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}

uint16_t __pic_get_ISR(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR); 

}



#endif // !PIC_H 
#define PIC_H 

