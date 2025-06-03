#ifndef PIC_H
#define PIC_H

#include "lib/common.h"

#define PIC_1_COMMAND   0x20
#define PIC_2_COMMAND   0xA0
#define PIC_1_DATA      0x21
#define PIC_2_DATA      0xA1

#define PIC_EOI         0x20

#define ICW1_ICW4       0x01    /* indicate that ICW4 is present */
#define ICW1_SINGLE     0x02    /* single cascade mode */
#define ICW1_INTERVAL4  0x04    /* call address interval 4 */
#define ICW1_LEVEL      0x80    /* level triggered (edge mode) */
#define ICW1_INIT       0x10    /* initialization */

#define ICW4_8068       0x01    /* bit 0 8086 mode */
#define ICW4_AUTO       0x02    /* bit 1 enable automatic EOI */
#define ICW4_BUF_SLAVE  0x08    /* bit 3 set and bit 2 cleared buffered mode */
#define ICW4_BUF_MASTER 0x0C    /* both 3 & 2 set buffered mode */
#define ICW4_SFNM       0x10    /* bit 4 sfnm enabled - interrupt priorities */

#define PIC_READ_IRR    0x0A
#define PIC_READ_ISR    0x0B

void _pic_sendEOI(uint8_t irq);
void _pic_remap(int offset1, int offset2);
void _pic_disable(void);
void IRQ_set_mask(uint8_t IRQ_line);
void IRQ_clear_mask(uint8_t IRQ_line);
uint16_t __pic_get_IRR(void);
uint16_t __pic_get_ISR(void);

#endif /* PIC_H */
