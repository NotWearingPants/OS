#include "shell.h"
#include "../common/screen_.h"
#include "../common/cmos_.h"
#include "../common/system_func_declaration.h"

#define PROMPT ">>"
#define PROMPT_LENGTH (sizeof(PROMPT) - 1)

uint8_t pos_y = 0;

void start_shell() {
    init_pointers();
    while (TRUE) {
        print_string(0, pos_y, PROMPT, DEFAULT_COLOR);

        char command[100];
        uint8_t length_command = string_read(PROMPT_LENGTH, pos_y, command);

        pos_y++;

        handle_command(command, length_command);
    }
}

void print_time(uint8_t x, uint8_t y, uint8_t color) {
    uint8_t seconds = read_from_cmos(CMOS_REG_SECONDS);
    uint8_t minutes = read_from_cmos(CMOS_REG_MINUTES);
    uint8_t hours = read_from_cmos(CMOS_REG_HOURS);
    uint8_t day = read_from_cmos(CMOS_REG_DAY);
    uint8_t month = read_from_cmos(CMOS_REG_MONTH);
    uint8_t year = read_from_cmos(CMOS_REG_YEAR);

    print_char(x + 0, y, (hours   / 0x10) + '0', color);
    print_char(x + 1, y, (hours   % 0x10) + '0', color);
    print_char(x + 2, y, ':'                   , color);
    print_char(x + 3, y, (minutes / 0x10) + '0', color);
    print_char(x + 4, y, (minutes % 0x10) + '0', color);
    print_char(x + 5, y, ':'                   , color);
    print_char(x + 6, y, (seconds / 0x10) + '0', color);
    print_char(x + 7, y, (seconds % 0x10) + '0', color);

    print_char(x + 10, y, (day    / 0x10) + '0', color);
    print_char(x + 11, y, (day    % 0x10) + '0', color);
    print_char(x + 12, y, '/'                  , color);

    print_char(x + 13, y, (month  / 0x10) + '0', color);
    print_char(x + 14, y, (month  % 0x10) + '0', color);
    print_char(x + 15, y, '/'                  , color);

    print_char(x + 16, y, (year   / 0x10) + '0', color);
    print_char(x + 17, y, (year   % 0x10) + '0', color);
}

void handle_command(char* command, uint8_t length_command) {
    char* arr_pos_arg[50];
    int count_words = string_split(command, ' ', arr_pos_arg);

    if (count_words > 1) {
        print_string(50, pos_y - 1, arr_pos_arg[1], DEFAULT_COLOR);
    }
    if (count_words > 0) {
        print_number(60, pos_y - 1, count_words - 1, DEFAULT_COLOR);
    }

    if (string_compare(arr_pos_arg[0], "time")) {
        print_time(0, pos_y, DEFAULT_COLOR);
        pos_y++;

    } else if (string_compare(arr_pos_arg[0], "read")) {
        if (count_words != 2) {
            print_string(0, pos_y++, "Usage: read <filename>", COLOR(LIGHT_RED, BLACK));
            return;
        }

        char file_content[255];
        if (!read_file(arr_pos_arg[1], file_content)) {
            print_string(0, pos_y++, "the file does not exist", COLOR(LIGHT_RED, BLACK));
            return;
        }

        print_string(0, pos_y++, file_content, DEFAULT_COLOR);

    } else if (string_compare(arr_pos_arg[0], "write")) {
        if (count_words != 2) {
            print_string(0, pos_y++, "Usage: write <filename>", COLOR(LIGHT_RED, BLACK));
            return;
        }

        char data[255];
        string_read(0, pos_y++, data);
        write_file(arr_pos_arg[1], data);

    } else if (!string_is_empty(command)) {
        print_string(0, pos_y, "'", DEFAULT_COLOR);
        print_string(1, pos_y, command, DEFAULT_COLOR);
        print_string(length_command + 1, pos_y, "' is not recognized as command", DEFAULT_COLOR);
        // print_string(string_size(command) + 1, pos_y, "' is not recognized as command", DEFAULT_COLOR);
        pos_y++;

    }
}
