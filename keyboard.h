#include "common.h"

#define KEYBOARD_IRQ 1

// #define CAPSLK      0x3a

void keyboard_handle_interrupt();
uint8_t get_char();
