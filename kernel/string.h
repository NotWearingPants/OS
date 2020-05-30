#ifndef _STRING_H_
#define _STRING_H_

#include "../common/common.h"
#include "../common/api/string.h"

#define X(return_type, name, parameters) return_type name parameters;
SYSTEM_FUNCS_STRING
#undef X

unsigned int string_copy(char* destination, char* source);
uint8_t string_size(char* string);
bool string_fall_space(char* string);

#endif
