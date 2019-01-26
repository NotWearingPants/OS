#include "filesystem.h"
#include "string.h"

void add_data_to_memory(char* str);
int find_file_in_pointerslist(char* file_name);

char memory[1000];
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
    int file_pos = find_file_in_pointerslist(filename);
    
    // file not exists
    if (file_pos == -1) {
        return FALSE;
    }

    string_copy(buffer, pointers[file_pos + 1]);
    return TRUE;	
}

void write_file(char* filename, char* contents) {
    if (is_file(filename)) {
        delete_file(filename);
    }
    
    add_data_to_memory(filename);
    add_data_to_memory(contents);
}

bool is_file(char* filename) {
    if (find_file_in_pointerslist(filename) == -1) {
        return FALSE;
    }

    return TRUE;
}

// pointers_count is wrong because this func
// this func destroys pointers count (add 2 to the val)
void delete_file(char* filename) {
    char* file_pointer;

    int file_addres_pos = find_file_in_pointerslist(filename);
    if (file_addres_pos == -1) {
        return;
    }
    
    file_pointer = pointers[file_addres_pos];

// in the memory saved name string and data string, we delet both
// better name required!
    
    // int num = 0;
    // for (int file_pos = 0; num != 2; file_pos++) {
    //     if (file_pointer[file_pos] == '\0') {
    //         num++;
    //     }

    //     file_pointer[file_pos] = '\0';
    // }

    
    int file_pos = 0;
    // delete file data and file name
    for (int i = 0; i < 2; i++) {
        for ( ; file_pointer + file_pos != '\0'; file_pos++) {
            *(file_pointer + file_pos) = '\0';
        }
        file_pos++;
    }

    // pointers_count -= 2;
}

int find_file_in_pointerslist(char* file_name) {
    for (int name_pos = 0; name_pos < pointers_count; name_pos += 2) {
        if (string_compare(file_name, pointers[name_pos])) {
            return name_pos;
        }
    }
    // file doesn't exists
    return -1;
}

void /*?*/ move_file(/* ? */) {
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
