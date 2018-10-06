#include "shell.h"
#include "cmos.h"
#include "screen.h"
#include "keyboard.h"
#include "string.h"
#include "filesystem.h"

#define PROMPT ">>"
#define PROMPT_LENGTH (sizeof(PROMPT) - 1)

volatile uint8_t pos_x = PROMPT_LENGTH;
uint8_t pos_y = 0;

// volatile bool enterPressed = FALSE;
volatile char command[100];

void update_cursor() {
    move_cursor(pos_x, pos_y);
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

void start_shell() {
    char key;
    while (TRUE) {
        // print prompt
        print_string(0, pos_y, PROMPT, DEFAULT_COLOR);
        update_cursor();

        // wait for interrupt of enter
        // TODO: while (!enterPressed); doesn't work
        
        key = get_char();
        shell_handle_key(key);

        if (key == '\n') {
            pos_y++;

            if (string_compare((char*)command, "time")) {
                print_time(0, pos_y, DEFAULT_COLOR);

                pos_y++;
            } else if (string_compare((char*)command, "read")) {
                print_string(0, pos_y, read_file("test.txt"), DEFAULT_COLOR);

                pos_y++;
            } else if (string_compare((char*)command, "write")) {
                write_file("test.txt", "hello");
            } else if (!string_is_empty((char*)command)) {
                print_string(0, pos_y, "'", DEFAULT_COLOR);
                print_string(1, pos_y, (char*)command, DEFAULT_COLOR);
                print_string(pos_x - (PROMPT_LENGTH - 1), pos_y, "' is not recognized as command", DEFAULT_COLOR);
                pos_y++;
            }

            pos_x = PROMPT_LENGTH;
        }
    }
}

void shell_handle_key(uint8_t key) {
    // we can miss some keys :(
    // if (enterPressed) {
    //     return;
    // }

    if (key == '\n') {
        command[pos_x - PROMPT_LENGTH] = '\0';
    }
    else {
        print_char(0 + pos_x, 0 + pos_y, key, DEFAULT_COLOR);
        command[pos_x - PROMPT_LENGTH] = key;
        pos_x++;
        update_cursor();
    }
}
