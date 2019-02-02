#include "math.h"

uint32_t power(uint32_t num, uint16_t n) {
    uint32_t sum = num;
    for (int i = 1; i < n; i++) {
        sum = sum * num;
    }

    if (n == 0) {
        return 1;
    }

    return sum;
}
