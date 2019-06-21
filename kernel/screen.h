#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "../common/screen_.h"
#include "common.h"

#define SCREEN_ADDRESS ((uint8_t*)0xb8000)
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void print_char(uint8_t x, uint8_t y, uint8_t character, uint8_t color);
uint8_t print_string(uint8_t x, uint8_t y, char *string, uint8_t color);
void move_cursor(uint8_t x, uint8_t y);
void print_number(uint8_t x, uint8_t y, uint32_t num, uint8_t color);
uint32_t power(uint32_t num, uint16_t n);

#endif
