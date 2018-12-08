#include "filesystem.h"
#include "string.h"

char memory[255];
char* pointers[255];
int count_files = 0;

// fix the size of the memory in the future

void add_data_to_memory(char* str) {
    static int pos = 0;
    static int count = 0;
    pointers[count] = &memory[pos];
    count++;

    for (int i = 0; str[i] != '\0'; i++, pos++) {
        memory[pos] = str[i];
    }
    memory[pos] = '\0';
    pos++;
}

///////////////////////////////////////////////////////////////
//                           FILES                           //
///////////////////////////////////////////////////////////////

char* read_file(char* filename) {
    char* error = "the file does not exist";
    for (int i = 0; i < count_files * 2; i += 2) {
        if (string_compare(filename, pointers[i])) {
            return pointers[i + 1];
        }
    }
    
    return error;
}

void write_file(char* filename, char* contents) {
    count_files++;
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
