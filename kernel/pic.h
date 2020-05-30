#include "../common/common.h"

#define PIC1_START 0x08
#define PIC2_START 0x70

#define IRQ(n) (((n) < 8 ? PIC1_START : PIC2_START) + (n))

void finish_interrupt(uint8_t interrupt_number);
