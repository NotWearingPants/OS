#include "filesystem.h"
#include "string.h"

char the_only_file[100];

///////////////////////////////////////////////////////////////
//                           FILES                           //
///////////////////////////////////////////////////////////////

char* read_file(char* filename) {
    return the_only_file;
}

void write_file(char* filename, char* contents) {
    string_copy(the_only_file, contents);
}

void /* TODO */ delete_file(/* TODO */) {
    // TODO
}

void /* TODO */ move_file(/* TODO */) {
    // TODO
}

void /* TODO */ is_file(/* TODO */) {
    // TODO
}

void /* TODO */ get_file_size(/* TODO */) {
    // TODO
}

///////////////////////////////////////////////////////////////
//                        DIRECTORIES                        //
///////////////////////////////////////////////////////////////

void /* TODO */ make_directory(/* TODO */) {
    // TODO
}

void /* TODO */ remove_directory(/* TODO */) {
    // TODO
}

void /* TODO */ move_directory(/* TODO */) {
    // TODO
}

void /* TODO */ is_directory(/* TODO */) {
    // TODO
}

void /* TODO */ get_directory_contents(/* TODO */) {
    // TODO
}
