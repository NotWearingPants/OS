#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "common.h"

#define SCREEN_ADDRESS ((uint8_t*)0xb8000)
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

enum Color {
    COLOR_BLACK         = 0x0,
    COLOR_BLUE          = 0x1,
    COLOR_GREEN         = 0x2,
    COLOR_AQUA          = 0x3,
    COLOR_RED           = 0x4,
    COLOR_PURPLE        = 0x5,
    COLOR_YELLOW        = 0x6,
    COLOR_WHITE         = 0x7,
    COLOR_GRAY          = 0x8,
    COLOR_LIGHT_BLUE    = 0x9,
    COLOR_LIGHT_GREEN   = 0xA,
    COLOR_LIGHT_AQUA    = 0xB,
    COLOR_LIGHT_RED     = 0xC,
    COLOR_LIGHT_PURPLE  = 0xD,
    COLOR_LIGHT_YELLOW  = 0xE,
    COLOR_BRIGHT_WHITE  = 0xF,
};

#define COLOR(text_color, background_color) ((((uint8_t)COLOR_##background_color) << 4) | ((uint8_t)COLOR_##text_color))

#define DEFAULT_COLOR COLOR(BRIGHT_WHITE, BLACK)

void print_char(uint8_t x, uint8_t y, uint8_t character, uint8_t color);
void print_string(uint8_t x, uint8_t y, char *string, uint8_t color);
void move_cursor(uint8_t x, uint8_t y);
void print_number(uint8_t x, uint8_t y, uint32_t num, uint8_t color);
uint32_t power(uint32_t num, uint16_t n);

#endif
