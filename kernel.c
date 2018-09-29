#include "kernel.h"
#include "screen.h"
#include "cmos.h"
#include "pic.h"

/// 8042 PS/2 Controller ///

// ports
#define DATA_PORT 0x60 // read & write data
#define STATUS_PORT 0x64 // read status
#define COMMAND_PORT 0x64 // write command

// commands
#define CMD_READ_CONTROLLER_OUTPUT 0xd0

#define ENTER       28
#define SPACE       57
#define CAPSLK      58

#define KEYBOARD_IRQ 1

#define DEFAULT_X   2




////////////////////////////

// void print_irq1() {
    
//     while (((inb(STATUS_PORT) >> 1) & 1) != 0);
//     outb(COMMAND_PORT, CMD_READ_CONTROLLER_OUTPUT);

//     while (((inb(STATUS_PORT) >> 0) & 1) != 1);
//     uint8_t controller_output = inb(DATA_PORT);

//     uint8_t irq1 = (controller_output >> 4) & 1;
//     if (irq1 == 1) {
//         print_char(2, 8, 'Y', 0x0f);
//     }

// }

uint16_t key[] = { '~', '~', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '~',
                   '~', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '~', '~',
                   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '~', '~', '~', '~', 'z',
                   'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '~', '~', '~', ' ' };
uint8_t enterPrees = 0;
char command[100];

static uint8_t pos_x = 2;
static uint8_t pos_y = 0;


void main() {
    print_new_line(0, 0x0f);

    while (TRUE) {
        if (enterPrees == 1) {
            enterPrees = 0;
            pos_y++;

            if (command[0] == 'A' && command[1] == 'm' && command[2] == 'i' && command[3] == 't' && command[4] == '\0') {
                print_time(0, pos_y, 0x0f);
                pos_y++;
            }
            else {
                print_string(0, pos_y, "'", 0x0f);
                print_string(1, pos_y, command, 0x0f);
                print_string(pos_x - (DEFAULT_X - 1), pos_y, "' is not recognized as command", 0x0f);

                pos_y++;
            }
            
            pos_x = DEFAULT_X;
            print_new_line(pos_y, 0x0f);

        }
    }
}

void handle_interrupt(uint8_t interrupt_number) {

    // keyboard interrupt
    if (interrupt_number == IRQ(KEYBOARD_IRQ)) {
        if (((inb(STATUS_PORT) >> 0) & 1) == 1) {
            uint8_t data = inb(DATA_PORT);

            if (data < 100) { 
                if (data == ENTER) {
                    command[pos_x - DEFAULT_X] = '\0';

                    enterPrees = 1;
                }
                else {
                    print_char(0 + pos_x, 0 + pos_y, key[data], 0x0f);
                    move_cursor(pos_x, pos_y);
                    command[pos_x - DEFAULT_X] = key[data];
                    pos_x++;
                }
 
            }
        }
    }

    finish_interrupt(interrupt_number);
}

void print_time(uint8_t x, uint8_t y, uint8_t color) {
    uint8_t seconds = read_from_cmos(CMOS_REG_SECONDS);
    uint8_t minutes = read_from_cmos(CMOS_REG_MINUTES);
    uint8_t hours = read_from_cmos(CMOS_REG_HOURS);
    uint8_t day = read_from_cmos(CMOS_REG_DAY);
    uint8_t month = read_from_cmos(CMOS_REG_MONTH);
    uint8_t year = read_from_cmos(CMOS_REG_YEAR);

    print_char(x + 0, y, (hours   / 0x10) + '0', color);
    print_char(x + 1, y, (hours   % 0x10) + '0', color);
    print_char(x + 2, y, ':'                   , color);
    print_char(x + 3, y, (minutes / 0x10) + '0', color);
    print_char(x + 4, y, (minutes % 0x10) + '0', color);
    print_char(x + 5, y, ':'                   , color);
    print_char(x + 6, y, (seconds / 0x10) + '0', color);
    print_char(x + 7, y, (seconds % 0x10) + '0', color);

    print_char(x + 10, y, (day    / 0x10) + '0', color);
    print_char(x + 11, y, (day    % 0x10) + '0', color);
    print_char(x + 12, y, '/'                  , color);

    print_char(x + 13, y, (month  / 0x10) + '0', color);
    print_char(x + 14, y, (month  % 0x10) + '0', color);
    print_char(x + 15, y, '/'                   , color);

    print_char(x + 16, y, (year   / 0x10) + '0', color);
    print_char(x + 17, y, (year   % 0x10) + '0', color);
}

void print_new_line(uint8_t line, uint8_t color) {
    move_cursor(2, line);
    print_string(0, line, ">>", 0x0f);
}
