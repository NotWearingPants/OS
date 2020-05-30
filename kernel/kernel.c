#include "kernel.h"
#include "screen.h"
#include "pic.h"
#include "keyboard.h"
// #include "../shell/shell.h"

#include "cmos.h"
#include "string.h"
#include "filesystem.h"

#include "../common/system_funcs.h"

#include "../shell_bin.h"

typedef void (*_start_t)();

void main() {
    void* func_arr[] = {
        #define X(return_type, name, parameters) (void*)name,
        SYSTEM_FUNCS
        #undef X
    };

    void*** arr_pointers = (void***)FUNC_ARR_ADDRESS;
    *arr_pointers = func_arr;

    ((_start_t)(shell_bin + 0x2A7))();
}

void handle_interrupt(uint8_t interrupt_number) {

    // keyboard interrupt
    if (interrupt_number == IRQ(KEYBOARD_IRQ)) {
        keyboard_handle_interrupt();
    }

    finish_interrupt(interrupt_number);
}
