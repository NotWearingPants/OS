#ifndef _API_STRING_H_
#define _API_STRING_H_

#include "../common.h"

#define SYSTEM_FUNCS_STRING \
    X(bool, string_compare, (char* left, char* right))                       \
    X(bool, string_is_empty, (char* command))                                \
    X(uint8_t, string_read, (uint8_t pos_x, uint8_t pos_y, char* buffer))    \
    X(unsigned int, string_split, (char* str, char delimeter, char** parts))

#endif
