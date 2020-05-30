#include "../common/api/cmos.h"

#define X(return_type, name, parameters) return_type name parameters;
SYSTEM_FUNCS_CMOS
#undef X
