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

uint8_t string_size(char* string) {
    uint8_t count = 0;

    while (TRUE) {
        if (string[count] == '\0') {
            return count;
        }
        count++;
    }
}

void string_split(char* commend, char* arg) {
    char arr[100];
    string_copy(arr, commend);
    
    int i = 0;
    for ( ; arr[i] != '|' ; i++) {
        commend[i] = arr[i];
    }
    commend[i] = '\0';

    int j = 0;
    for ( ; arr[i] != '\0'; i++, j++) {
        arg[j] = arr[i];
    }
    arg[j] = '\0';

}

void string_append(char* destination, char* source) {
    // print_number(10, 15, string_size(destination), DEFAULT_COLOR);
    /*
    for (int i = 0; ; i++) {
        destination[string_size(destination) + 1 + i] = source[i];

        if (source[i] == '\0') {
            break;
        }
    }*/
}
