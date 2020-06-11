#include "memory.h"

void memory_copy(char* source, char* destination, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        destination[i] = source[i];
    }
}
