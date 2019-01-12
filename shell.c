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
        // uint8_t length_command = string_read(PROMPT_LENGTH, pos_y, command);
        int length_command = shell_input(PROMPT_LENGTH, pos_y, command);
        if (special_key_press(command[0])) {
            if (command[0] == UP_KEY) {
                print_char(2, 0, 'U', DEFAULT_COLOR);
            }
        }
        else {
            pos_y++;

            handle_command(command, length_command);
        }
    }
}

int shell_input(uint8_t pos_x, uint8_t pos_y, char* buffer) {
    char key = ' ';
    int length_command = 0;
    
    move_cursor(pos_x + length_command, pos_y);

    while (TRUE) {
        key = get_char();
        if (key == '\n') {
            buffer[length_command] = '\0';
            break;
        }
        
        if (key == RIGHT_KEY || key == LEFT_KEY || key == UP_KEY || key == DOUN_KEY) {
            buffer[0] = key;
            buffer[1] = '\0';
            length_command = 1;
            break;
        }

        if (key == DELETE) {
            if (length_command > 0) {
                length_command--;
                print_char(pos_x + length_command, pos_y, ' ', DEFAULT_COLOR);
                buffer[length_command] = ' ';
            }
        }
        else {
            print_char(pos_x + length_command, pos_y, key, DEFAULT_COLOR);

            buffer[length_command] = key;
            length_command++;
        }

        move_cursor(pos_x + length_command, pos_y);
    }

    return length_command;
}

bool special_key_press(char key) {
    int special_key[] = { RIGHT_KEY, LEFT_KEY, UP_KEY, DOUN_KEY, };

    // 4 is a natural number chaing it
    for (int i = 0; i < 4; i++) {
        if (key == special_key[i]) {
            return TRUE;
        }
    }

    return FALSE;
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
    char* arr_pos_argv[50];
    int count_words = string_split(command, ' ', arr_pos_argv);

    if (count_words > 1) {
        print_string(50, pos_y - 1, arr_pos_argv[1], DEFAULT_COLOR);
    }
    if (count_words > 0) {
        print_number(60, pos_y - 1, count_words - 1, DEFAULT_COLOR);
    }

    if (string_compare(command, "time")) {
        print_time(0, pos_y, DEFAULT_COLOR);
        pos_y++;

    } else if (string_compare(command, "read")) {
        // print_string(0, pos_y, read_file(arr_pos_argv[1]), DEFAULT_COLOR);
        pos_y++;

    } else if (string_compare(command, "write")) {
        // write_file(arr_pos_argv[1], "text");
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
