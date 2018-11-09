#include "string.h"
#include "keyboard.h"
#include "screen.h"
#include "common.h"


bool string_compare(char* left, char* right) {
    int i = 0;
    while (left[i] != '\0') {
        if (left[i] != right[i]) {
            return FALSE;
        }
        i++;
    }

    if (right[i] != '\0') {
        return FALSE;
    }

    return TRUE;
}

bool string_is_empty(char* command) {
    if (command[0] == '\0') {
        return TRUE;
    }

    return FALSE;
}

void string_copy(char* destination, char* source) {
    for (int i = 0; ; i++) {
        destination[i] = source[i];
        if (source[i] == '\0') {
            break;
        }
    }
}

uint8_t string_read(uint8_t pos_x, uint8_t pos_y, char* buffer) {
    char key;
    uint8_t length_command = 0;

    while (TRUE) {
        key = get_char();
        buffer[length_command] = key;

        if (key == '\n') {
            buffer[length_command] = '\0';
            return length_command;
        }
        print_char(length_command + pos_x, pos_y, key, DEFAULT_COLOR);
        length_command++;
        move_cursor(length_command + pos_x, pos_y);

    }

    return 0;
}
