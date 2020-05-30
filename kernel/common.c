#include "common.h"

void outb(uint16_t port, uint8_t value) {
    __asm volatile("outb %b0, %w1"
        :
        : "a"(value), "d"(port)
    );
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm volatile("inb %1, %0"
        : "=a"(ret)
        : "Nd"(port)
    );

    return ret;
}
