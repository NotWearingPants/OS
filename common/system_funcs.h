#ifndef _SYSTEM_FUNCS_H_
#define _SYSTEM_FUNCS_H_

#include "common.h"

#define FUNC_ARR_ADDRESS (0x6C00)

#define SYSTEM_FUNCS \
    X(uint8_t, print_string, (uint8_t x, uint8_t y, char *string, uint8_t color)) \
    X(void, print_number, (uint8_t x, uint8_t y, uint32_t num, uint8_t color))    \
    X(uint8_t, string_read, (uint8_t pos_x, uint8_t pos_y, char* buffer))         \
    X(uint8_t, read_from_cmos, (uint8_t reg))                                     \
    X(unsigned int, string_split, (char* str, char delimeter, char** parts))      \
    X(bool, string_compare, (char* left, char* right))                            \
    X(bool, read_file, (char* filename, char* buffer))                            \
    X(void, write_file, (char* filename, char* contents))                         \
    X(bool, string_is_empty, (char* command))                                     \
    X(void, print_char, (uint8_t x, uint8_t y, uint8_t character, uint8_t color)) \
    X(uint32_t, power, (uint32_t num, uint16_t n))

#endif
