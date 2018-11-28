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

// instead of copying the characters, change string in place (replace delimeter with '\0' like old code)
// int string_split(char* string, char delimeter, char* arr[], int size) {
int string_split(char* string, char delimeter) {

    int count_words = 1;
    for (int i = 0; string[i] != '\0' ; i++) {
        if (string[i] == delimeter) {
            string[i] = '\0';
            count_words++;
        }
    }

    return count_words;



    // int count = 0;
    // for (int i = 0, pos = 0; string[i] != '\0'; i++, pos++) {
    //     if (string[i] == delimeter) {
    //         arr[count][pos] = '\0';
    //         count++;
    //         if (count == size) {
    //             break;
    //         }
    //         pos = 0;
    //         i++;
    //     }
    //     arr[count][pos] = string[i];
    // }

    // return count;
}

void string_append(char* arr1, char* arr2) {
    // print_number(10, 15, string_size(destination), DEFAULT_COLOR);
    //char new_arr[100];
    
    
    /*
    for (int i = 0; ; i++) {
        if (arr1[i] != '\0') {
            new_arr[i] = arr1[i];
        }
        else if (arr2[i] != '\0') {
            new_arr[i] = arr2[i];
        }
    }
    */
}
