#ifndef _STRING_H_
#define _STRING_H_

#include "common.h"

bool string_compare(char* left, char* right);
bool string_is_empty(char* command);
unsigned int string_copy(char* destination, char* source);
uint8_t string_read(uint8_t pos_x, uint8_t pos_y, char* buffer);
uint8_t string_size(char* string);
unsigned int string_split(char* str, char delimeter, char** parts);
bool string_fall_space(char* string);

#endif