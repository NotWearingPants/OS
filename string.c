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
    uint8_t length_command;

    for (length_command = 0; ; length_command++) {
        move_cursor(pos_x + length_command, pos_y);
        char key = get_char();

        if (key == '\n') {
            break;
        }

        buffer[length_command] = key;
        print_char(pos_x + length_command, pos_y, key, DEFAULT_COLOR);
    }

    buffer[length_command] = '\0';
    return length_command;
}
