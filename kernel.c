#include "kernel.h"
#include "screen.h"
#include "pic.h"
#include "keyboard.h"

void main() {
    start_shell();
}

void handle_interrupt(uint8_t interrupt_number) {

    // keyboard interrupt
    if (interrupt_number == IRQ(KEYBOARD_IRQ)) {
        keyboard_handle_interrupt();
    }

    finish_interrupt(interrupt_number);
}
