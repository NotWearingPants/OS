#ifndef _SYSTEM_FUNC_DISCALIMER_H_
#define _SYSTEM_FUNC_DISCALIMER_H_

#include "../kernel/common.h"

static uint8_t (*print_string)(uint8_t x, uint8_t y, char *string, uint8_t color);
static void (*print_number)(uint8_t x, uint8_t y, uint32_t num, uint8_t color);
static uint8_t (*string_read)(uint8_t pos_x, uint8_t pos_y, char* buffer);
static uint8_t (*read_from_cmos)(uint8_t reg);
static unsigned int (*string_split)(char* str, char delimeter, char** parts);
static bool (*string_compare)(char* left, char* right);
static bool (*read_file)(char* filename, char* buffer);
static void (*write_file)(char* filename, char* contents);
static bool (*string_is_empty)(char* command);
static void (*print_char)(uint8_t x, uint8_t y, uint8_t character, uint8_t color);

static void init_pointers()
{
    void*** arr_pointers = (void***)0x6C00;
    void** func_arr = *arr_pointers;

    print_string    = (uint8_t (*)(uint8_t x, uint8_t y, char *string, uint8_t color))  (func_arr[0]);
    print_number    = (void (*)(uint8_t x, uint8_t y, uint32_t num, uint8_t color))     (func_arr[1]);
    string_read     = (uint8_t (*)(uint8_t pos_x, uint8_t pos_y, char* buffer))         (func_arr[2]);
    read_from_cmos  = (uint8_t (*)(uint8_t reg))                                        (func_arr[3]);
    string_split    = (unsigned int (*)(char* str, char delimeter, char** parts))       (func_arr[4]);
    string_compare  = (bool (*)(char* left, char* right))                               (func_arr[5]);
    read_file       = (bool (*)(char* filename, char* buffer))                          (func_arr[6]);
    write_file      = (void (*)(char* filename, char* contents))                        (func_arr[7]);
    string_is_empty = (bool (*)(char* command))                                         (func_arr[8]);
    print_char      = (void (*)(uint8_t x, uint8_t y, uint8_t character, uint8_t color))(func_arr[9]);

}

#endif