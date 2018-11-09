#include "filesystem.h"
#include "string.h"

char the_only_file[100];

char* read_file(char* filename) {
    return the_only_file;
}

void write_file(char* filename, char* contents) {
    string_copy(the_only_file, contents);
}
