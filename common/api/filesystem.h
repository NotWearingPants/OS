#ifndef _API_FILESYSTEM_H_
#define _API_FILESYSTEM_H_

#include "../common.h"

/////////////////
//    FILES    //
/////////////////
#define SYSTEM_FUNCS_FILESYSTEM_FILES                     \
    X(bool, read_file, (char* filename, char* buffer))    \
    X(void, write_file, (char* filename, char* contents)) \
    X(void, delete_file, (char* filename))                \
    X(void /*?*/, move_file, (/* ? */))                   \
    X(bool, is_file, (char* filename))                    \
    X(void /*?*/, get_file_size, (/* ? */))

/////////////////
// DIRECTORIES //
/////////////////
#define SYSTEM_FUNCS_FILESYSTEM_DIRECTORIES               \
    X(void /*?*/, make_directory, (/* ? */))              \
    X(void /*?*/, remove_directory, (/* ? */))            \
    X(void /*?*/, move_directory, (/* ? */))              \
    X(void /*?*/, is_directory, (/* ? */))                \
    X(void /*?*/, get_directory_contents, (/* ? */))

#define SYSTEM_FUNCS_FILESYSTEM         \
    SYSTEM_FUNCS_FILESYSTEM_FILES       \
    SYSTEM_FUNCS_FILESYSTEM_DIRECTORIES

#endif
