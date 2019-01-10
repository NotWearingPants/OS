#include "common.h"

#define KEYBOARD_IRQ 1

#define LEFT_KEY    1
#define RIGHT_KEY   2
#define UP_KEY      3
#define DOUN_KEY    4

// #define CAPSLK      0x3a

void keyboard_handle_interrupt();
uint8_t get_char();
bool key_pressed();