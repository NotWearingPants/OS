#ifndef _SYSTEM_FUNCS_H_
#define _SYSTEM_FUNCS_H_

#include "api/screen.h"
#include "api/string.h"
#include "api/cmos.h"
#include "api/filesystem.h"

#define FUNC_ARR_ADDRESS (0x6C00)

#define SYSTEM_FUNCS        \
    SYSTEM_FUNCS_SCREEN     \
    SYSTEM_FUNCS_STRING     \
    SYSTEM_FUNCS_CMOS       \
    SYSTEM_FUNCS_FILESYSTEM

#endif
