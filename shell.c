#include "shell.h"
#include "cmos.h"
#include "screen.h"
#include "keyboard.h"
#include "string.h"

#define PROMPT ">>"
#define PROMPT_LENGTH (sizeof(PROMPT) - 1)

volatile uint8_t pos_x = PROMPT_LENGTH;
uint8_t pos_y = 0;

volatile bool enterPressed = FALSE;
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
    while (TRUE) {
        // print prompt
        print_string(0, pos_y, PROMPT, DEFAULT_COLOR);
        pos_x = PROMPT_LENGTH;
        update_cursor();

        // wait for interrupt of enter
        // TODO: while (!enterPressed); doesn't work
        while (enterPressed != TRUE);

        enterPressed = FALSE;
        pos_y++;

        // if (command[0] == 't' && command[1] == 'i' && command[2] == 'm' && command[3] == 'e' && command[4] == '\0') {
        if (string_compare((char*)command, "time")) {
            print_time(0, pos_y, DEFAULT_COLOR);

            pos_y++;
        }
        else {
            print_string(0, pos_y, "'", DEFAULT_COLOR);
            print_string(1, pos_y, (char*)command, DEFAULT_COLOR);
            print_string(pos_x - (PROMPT_LENGTH - 1), pos_y, "' is not recognized as command", DEFAULT_COLOR);

            pos_y++;
        }
    }
}

void shell_handle_key(uint8_t key) {
    // we can miss some keys :(
    if (enterPressed) {
        return;
    }

    if (key == '\n') {
        command[pos_x - PROMPT_LENGTH] = '\0';

        enterPressed = TRUE;
    }
    else {
        print_char(0 + pos_x, 0 + pos_y, key, DEFAULT_COLOR);
        command[pos_x - PROMPT_LENGTH] = key;
        pos_x++;
        update_cursor();
    }
}
