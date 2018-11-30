#include "shell.h"
#include "cmos.h"
#include "screen.h"
#include "keyboard.h"
#include "string.h"
#include "filesystem.h"

#define PROMPT ">>"
#define PROMPT_LENGTH (sizeof(PROMPT) - 1)

uint8_t pos_y = 0;


void start_shell() {

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
    int* argv = string_split(command, ' ');
    print_string(48, pos_y - 1, ixtract_argv(command, argv, 1), DEFAULT_COLOR);
    // print_string(50, pos_y - 1, command, DEFAULT_COLOR);

    if (string_compare(command, "time")) {
        print_time(0, pos_y, DEFAULT_COLOR);
        pos_y++;

    } else if (string_compare(command, "read")) {
        print_string(0, pos_y, read_file("test.txt"), DEFAULT_COLOR);
        pos_y++;

    } else if (string_compare(command, "write")) {
        // write_file(0, pos_y, command, argv);
        pos_y++;

    } else if (!string_is_empty(command)) {
        print_string(0, pos_y, "'", DEFAULT_COLOR);
        print_string(1, pos_y, command, DEFAULT_COLOR);
        print_string(length_command + 1, pos_y, "' is not recognized as command", DEFAULT_COLOR);
        // print_string(string_size(command) + 1, pos_y, "' is not recognized as command", DEFAULT_COLOR);
        pos_y++;
        
    }
}

bool check_write_syntax(char* command) {
    char arr[] = "write ";
    int size = string_size(arr);
    for (int i = 0; i < size; i++) {
        if (command[i] != arr[i]) {
            return 0;
        }
    }

    char name[100];
    for (int i = 0; command[size + i] != '\0'; i++) {
        name[i] = command[size + i];
    }

    print_string(10, 10, name, DEFAULT_COLOR);

    return 1;
}

char* ixtract_argv(char* string, int* arr, int argv_num) {
    static char argv[50] = { '\0' };
    int i = 0;
    for ( ; string[arr[argv_num + i]] != '\0'; i++) {
        argv[i] = string[arr[argv_num] + i];
    }
    argv[i] = '\0';
    return argv;
}