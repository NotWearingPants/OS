#include "filesystem.h"
#include "string.h"
#include "memory.h"

#define FILE_NOT_FOUND     (-1)

void add_data_to_memory(char* data, unsigned int size);
void add_str_to_memory(char* str);
int find_file_in_pointerslist(char* file_name);

char memory[1000];
char* pointers[255];
int pointers_count = 0;
int pos = 0;

// fix the size of the memory in the future

void add_data_to_memory(char* data, unsigned int size) {
    pointers[pointers_count] = &memory[pos];
    pointers_count++;

    memory_copy(&memory[pos], data, size);
    pos += size;
}

void add_str_to_memory(char* str) {
    pointers[pointers_count] = &memory[pos];
    pointers_count++;

    int str_size = string_copy(&memory[pos], str);
    pos += str_size + 1; // +1 for the null terminator
}

int find_file_in_pointerslist(char* file_name) {
    for (int name_pos = 0; name_pos < pointers_count; name_pos += 2) {
        if (string_compare(file_name, pointers[name_pos])) {
            return name_pos;
        }
    }
    // if file doesn't exists return not possible value for arr
    return FILE_NOT_FOUND;
}

///////////////////////////////////////////////////////////////
//                           FILES                           //
///////////////////////////////////////////////////////////////

bool read_file(char* filename, char* buffer) {
    int file_pos = find_file_in_pointerslist(filename);
    
    // file not exists
    if (file_pos == FILE_NOT_FOUND) {
        return FALSE;
    }

    string_copy(buffer, pointers[file_pos + 1]);
    return TRUE;	
}

void write_file(char* filename, char* contents, unsigned int size) {
    delete_file(filename);
    
    add_str_to_memory(filename);
    add_data_to_memory(contents, size);
}

// pointers_count is wrong because this func
void delete_file(char* filename) {
    char* file_pointer;

    int file_addres_pos = find_file_in_pointerslist(filename);
    if (file_addres_pos == FILE_NOT_FOUND) {
        return;
    }
    
    file_pointer = pointers[file_addres_pos];

    int file_pos = 0;
    // delete file data and file name
    for (int i = 0; i < 2; i++) {
        for ( ; *(file_pointer + file_pos) != '\0'; file_pos++) {
            *(file_pointer + file_pos) = '\0';
        }
        // skip on the end char ('\0') of the string name 
        file_pos++;
    }

    // pointers_count -= 2;
}

void /*?*/ move_file(/* ? */) {
    // TODO
}

bool is_file(char* filename) {
    if (find_file_in_pointerslist(filename) == FILE_NOT_FOUND) {
        return FALSE;
    }

    return TRUE;
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
