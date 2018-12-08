#include "filesystem.h"
#include "string.h"

char memory[255];
char* pointers[255];
int pointers_count = 0;

// fix the size of the memory in the future

void add_data_to_memory(char* str) {
    static int pos = 0;
    pointers[pointers_count] = &memory[pos];
    pointers_count++;

    int str_size = string_copy(&memory[pos], str);
    pos += str_size + 1; // +1 for the null terminator
}

///////////////////////////////////////////////////////////////
//                           FILES                           //
///////////////////////////////////////////////////////////////

bool read_file(char* filename, char* buffer) {
    for (int i = 0; i < pointers_count; i += 2) {
        if (string_compare(filename, pointers[i])) {
            string_copy(buffer, pointers[i + 1]);
            return TRUE;
        }
    }

    return FALSE;
}

void write_file(char* filename, char* contents) {
    add_data_to_memory(filename);
    add_data_to_memory(contents);
}

void /*?*/ delete_file(/* ? */) {
    // TODO
}

void /*?*/ move_file(/* ? */) {
    // TODO
}

void /*?*/ is_file(/* ? */) {
    // TODO
}

void /*?*/ get_file_size(/* ? */) {
    // TODO
}

///////////////////////////////////////////////////////////////
//                        DIRECTORIES                        //
///////////////////////////////////////////////////////////////

void /*?*/ make_directory(/* ? */) {
    // TODO
}

void /*?*/ remove_directory(/* ? */) {
    // TODO
}

void /*?*/ move_directory(/* ? */) {
    // TODO
}

void /*?*/ is_directory(/* ? */) {
    // TODO
}

void /*?*/ get_directory_contents(/* ? */) {
    // TODO
}
