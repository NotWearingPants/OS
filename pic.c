#include "pic.h"

#define PIC1_CMD 0x20
#define CMD_END_OF_INTERRUPT 0x20

void finish_interrupt(uint8_t interrupt_number) {
    if (8 <= interrupt_number && interrupt_number <= 15) {
        outb(PIC1_CMD, CMD_END_OF_INTERRUPT);
    }
}
