#ifndef _SYSTEM_FUNC_DECLARATION_H_
#define _SYSTEM_FUNC_DECLARATION_H_

#include "system_funcs.h"

#define X(return_type, name, parameters) typedef return_type (*name##_t)parameters;
SYSTEM_FUNCS
#undef X

#define X(return_type, name, parameters) extern name##_t name;
SYSTEM_FUNCS
#undef X

void init_pointers();

#endif
