#include "cmos.h"

uint8_t read_from_cmos(uint8_t reg) {
    outb(0x70, reg);
    return inb(0x71);
}
