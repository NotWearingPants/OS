#include "system_func_declaration.h"

#define X(return_type, name, parameters) name##_t name;
SYSTEM_FUNCS
#undef X

void init_pointers()
{
    void*** arr_pointers = (void***)FUNC_ARR_ADDRESS;
    void** func_arr = *arr_pointers;

    int i = 0;

    #define X(return_type, name, parameters) name = (name##_t)(func_arr[i++]);
    SYSTEM_FUNCS
    #undef X
}
