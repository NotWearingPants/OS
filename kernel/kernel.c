#include "kernel.h"
#include "screen.h"
#include "pic.h"
#include "keyboard.h"
#include "../shell/shell.h"

#include "cmos.h"
#include "string.h"
#include "filesystem.h"

#include "../common/system_funcs.h"

void main() {
    void* func_arr[] = {
        #define X(return_type, name, parameters) (void*)name,
        SYSTEM_FUNCS
        #undef X
    };

    void*** arr_pointers = (void***)FUNC_ARR_ADDRESS;
    *arr_pointers = func_arr;

    start_shell();
}

void handle_interrupt(uint8_t interrupt_number) {

    // keyboard interrupt
    if (interrupt_number == IRQ(KEYBOARD_IRQ)) {
        keyboard_handle_interrupt();
    }

    finish_interrupt(interrupt_number);
}
