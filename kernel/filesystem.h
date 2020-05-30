#include "../common/common.h"
#include "../common/api/filesystem.h"

#define X(return_type, name, parameters) return_type name parameters;
SYSTEM_FUNCS_FILESYSTEM
#undef X
