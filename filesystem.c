#include "filesystem.h"

char* the_only_file = "";

char* read_file(char* filename) {
    return the_only_file;
}

void write_file(char* filename, char* contents) {
    the_only_file = contents;
}
