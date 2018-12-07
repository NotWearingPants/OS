#include "filesystem.h"
#include "string.h"

char the_only_file[255];
char* poiters[255];
int count_files = 0;

// fix the size of the memory in thr fucher

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
    char* error = "the file does not exist";
    for (int i = 0; i < count_files * 2; i += 2) {
        if (string_compare(filename, poiters[i])) {
            return poiters[i + 1];
        }
    }
    
    return error;
}

void write_file(char* filename, char* contents) {
    count_files++;
    add_data(filename);
    add_data(contents);
}
