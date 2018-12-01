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
