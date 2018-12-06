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
    #define DELETE      127
    uint8_t length_command = 0;

    char key = ' ';
    while (TRUE) {
        move_cursor(pos_x + length_command, pos_y);
        key = get_char();

        if (key == '\n') {
            break;
        }

        // not the best code :( bat work.
        if (key == DELETE) {
            if (length_command > 0) {
                length_command--;
                print_char(pos_x + length_command, pos_y, ' ', DEFAULT_COLOR);
                buffer[length_command] = ' ';
            }
        }
        else {
            buffer[length_command] = key;
            print_char(pos_x + length_command, pos_y, key, DEFAULT_COLOR);
            length_command++;
        }

    }
    
    buffer[length_command] = '\0';
    return length_command;

    // for (length_command = 0; ; length_command++) {
    //     move_cursor(pos_x + length_command, pos_y);
    //     char key = get_char();

    //     if (key == '\n') {
    //         break;
    //     }

    //     if (key == DELETE && length_command > 0) {
    //         length_command--;
    //         key = ' ';
    //     }

    //     buffer[length_command] = key;
    //     print_char(pos_x + length_command, pos_y, key, DEFAULT_COLOR);
    // }

    // buffer[length_command] = '\0';
    // return length_command;
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

bool string_fall_space(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] != ' ') {
            return 0;
        }
    }

    return 1;
}

void string_split(char* string, char delimeter, char** arr) {
    static char q = '\0';

    int count = 0;
    int i = 0;
    for (; string[i] == delimeter; i++);
    arr[count] = &string[i];
    count++;

    for (; string[i] != '\0'; i++) {
        if (string[i] == delimeter) {
            string[i] = '\0';
            
            if (string[i + 1] != delimeter) {
                arr[count] = &string[i + 1];
                count++;
            }
        }
    }

    arr[count] = &q;
}

void string_combination(char* arr1, char* arr2, char* buffer) {
    int i = 0;
    for (; arr1[i] != '\0'; i++) {
        buffer[i] = arr1[i];
    }
    for (int j = 0; arr2[j] != '\0'; i++, j++) {
        buffer[i] = arr2[j];
    }
    
}
