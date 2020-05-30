#ifndef _SYSTEM_FUNC_DECLARATION_H_
#define _SYSTEM_FUNC_DECLARATION_H_

#include "system_funcs.h"

#define X(return_type, name, parameters) typedef return_type (*name##_t)parameters;
SYSTEM_FUNCS
#undef X

#define X(return_type, name, parameters) static name##_t name;
SYSTEM_FUNCS
#undef X

static void init_pointers()
{
    void*** arr_pointers = (void***)FUNC_ARR_ADDRESS;
    void** func_arr = *arr_pointers;

    int i = 0;

    #define X(return_type, name, parameters) name = (name##_t)(func_arr[i++]);
    SYSTEM_FUNCS
    #undef X
}

#endif
