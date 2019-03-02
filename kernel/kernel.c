#include "kernel.h"
#include "screen.h"
#include "pic.h"
#include "keyboard.h"
#include "../shell/shell.h"


#include "../kernel/cmos.h"
#include "../kernel/screen.h"
#include "../kernel/keyboard.h"
#include "../kernel/string.h"
#include "../kernel/filesystem.h"

void** pointer = 0x6c00;

void main() {
    void* func_arr[] = { 
        (void*)print_string, (void*)print_number, (void*)string_read, (void*)read_from_cmos,
        (void*)read_from_cmos, (void*)string_split, (void*)string_compare, (void*)read_file,
        (void*)string_read,  (void*)write_file, (void*)string_is_empty, 
        };
    
    pointer = func_arr; 

    start_shell();
}

void handle_interrupt(uint8_t interrupt_number) {

    // keyboard interrupt
    if (interrupt_number == IRQ(KEYBOARD_IRQ)) {
        keyboard_handle_interrupt();
    }

    finish_interrupt(interrupt_number);
}
