#include "pic.h"

void _pic_sendEOI(uint8_t irq)
{
    /* if irq came from master, issue EOI to master only */
    /* if irq came from slave (irq >= 8), issue to both */
    if (irq >= 8)
    {
        outb(PIC_2_COMMAND, PIC_EOI);
    }
    outb(PIC_1_COMMAND, PIC_EOI); /* always issue to master */
}

void _pic_remap(int offset1, int offset2)
{
    /* initiate initialization sequence (cascade mode) */
    outb(PIC_1_COMMAND, ICW1_INIT | ICW1_ICW4);

    /* slave initialization */
    io_wait();
    outb(PIC_2_COMMAND, ICW1_INIT | ICW1_ICW4);

    /* offset of PIC: master=32-39(0x20), slave=40-47(0x28) */
    io_wait();
    outb(PIC_1_DATA, offset1);
    io_wait();
    outb(PIC_2_DATA, offset2);

    /* ----CASCADE MODE CONFIG---- */
    /* for cascading - connect to IRQ line 2 */
    io_wait();
    outb(PIC_1_DATA, 0x04);

    /* tell slave master IRQ2 value in binary */
    io_wait();
    outb(PIC_2_DATA, 0x02);

    /* ----ICW4 CONFIG---- */
    io_wait();
    outb(PIC_1_DATA, ICW4_8068);
    io_wait();
    outb(PIC_2_DATA, ICW4_8068);

    /* unmask both PICs */
    outb(PIC_1_DATA, 0);
    outb(PIC_2_DATA, 0);
}

void _pic_disable(void)
{
    outb(PIC_1_DATA, 0xFF);
    outb(PIC_2_DATA, 0xFF);
}

void IRQ_set_mask(uint8_t IRQ_line)
{
    uint16_t port;
    uint8_t value;

    if (IRQ_line < 8) {
        port = PIC_1_DATA;
    } else {
        port = PIC_2_DATA;
        IRQ_line -= 8;
    }
    /* mask current value of IMR with mask value */
    value = inb(port) | (1 << IRQ_line);
    outb(port, value);
}

void IRQ_clear_mask(uint8_t IRQ_line)
{
    uint16_t port;
    uint8_t value;

    if (IRQ_line < 8) {
        port = PIC_1_DATA;
    } else {
        port = PIC_2_DATA;
        IRQ_line -= 8;
    }
    value = inb(port) & ~(1 << IRQ_line);
    outb(port, value);
}

static uint16_t __pic_get_irq_reg(int ocw_3)
{
    /* make IRR and ISR readable */
    outb(PIC_1_COMMAND, ocw_3);
    outb(PIC_2_COMMAND, ocw_3);

    /* read master and slave PIC */
    return (inb(PIC_2_COMMAND) << 8) | inb(PIC_1_COMMAND);
}

uint16_t __pic_get_IRR(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}

uint16_t __pic_get_ISR(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}

