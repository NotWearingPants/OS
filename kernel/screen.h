#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "../common/common.h"
#include "../common/api/screen.h"

#define SCREEN_ADDRESS ((uint8_t*)0xb8000)

#define X(return_type, name, parameters) return_type name parameters;
SYSTEM_FUNCS_SCREEN
#undef X

#endif
