#include "filesystem.h"
#include "string.h"

char the_only_file[255];
char* poiters[255];

void add_data(char* str) {
    static int pos = 0;
    static int count = 0;
    poiters[count] = &the_only_file[pos];
    count++;

    for (int i = 0; str[i] != '\0'; i++, pos++) {
        the_only_file[pos] = str[i];
    }
    the_only_file[pos] = '\0';
    pos++;
}

char* read_file(char* filename) {
    char* error = "error";
    if (string_compare(filename, poiters[0])) {
        return poiters[1];
    }
    else {
        return error;
    }
}

void write_file(char* filename, char* contents) {
    // char name[50];
    // int size = string_size(filename);
    // string_copy(name, filename);

    // name[size + 0] = ' ';
    // name[size + 1] = '\0';

    // string_combination(filename, contents, the_only_file);

    add_data(filename);
    add_data(contents);
}
