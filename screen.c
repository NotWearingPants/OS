#include "screen.h"
#include "math.h"

void print_char(uint8_t x, uint8_t y, uint8_t character, uint8_t color) {
    uint16_t pos = (uint16_t)y * SCREEN_WIDTH + x;

    SCREEN_ADDRESS[2 * pos + 0] = character;
    SCREEN_ADDRESS[2 * pos + 1] = color;
}

void print_string(uint8_t x, uint8_t y, char *string, uint8_t color) {
    for (int i = 0; string[i] != '\0'; i++) {
        print_char(x + i, y, (uint8_t)string[i], color);
    }
}

void print_number(uint8_t x, uint8_t y, uint32_t num, uint8_t color) {
    uint8_t count = 1;
    uint8_t sum = num;
    while (TRUE) {
        sum /= 10;
        if (sum == 0) {
            break;
        }
        count++;
    }

    int pos = 0;
    for (int i = count; i >= 1; i--) {
        print_char(x + pos, y, '0' + ((num / power(10, i - 1)) % 10), color);
        pos++;
    }

}

void move_cursor(uint8_t x, uint8_t y) {
	uint16_t pos = (uint16_t)y * SCREEN_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)((pos >> 0) & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}
