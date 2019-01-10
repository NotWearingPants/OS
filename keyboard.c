#include "keyboard.h"
#include "shell.h"

/// 8042 PS/2 Controller ///

// ports
#define DATA_PORT 0x60 // read & write data
#define STATUS_PORT 0x64 // read status
#define COMMAND_PORT 0x64 // write command

// commands
#define CMD_READ_CONTROLLER_OUTPUT 0xd0

// you can always read status, without IS_PREPARED_TO_READ
#define READ_STATUS()           (inb(STATUS_PORT))
#define READ_DATA()             (inb(DATA_PORT))
#define WRITE_DATA(value)       (outb(DATA_PORT, (value)))
#define WRITE_COMMAND(command)  (outb(COMMAND_PORT, (command)))

#define IS_PREPARED_TO_READ()   (GET_BIT(READ_STATUS(), 0) == 1)
#define IS_PREPARED_TO_WRITE()  (GET_BIT(READ_STATUS(), 1) == 0)

#define PREPARE_TO_READ()       while (!IS_PREPARED_TO_READ())
#define PREPARE_TO_WRITE()      while (!IS_PREPARED_TO_WRITE())

// special key
#define UP          200
#define LEFT        203
#define RIGHT       205
#define DOWN        208
#define DELETE      211
#define START       219

const uint8_t key_map[] = {
    '\0', '\0', '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',  '-',  '=',  127, '\0',  // 15
    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p',  '[',  ']',  '\n', '\0', 'a',  's',  // 31
    'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '\0', '\0', '\0', '\0', 'z',  'x',  'c',  'v',  // 47
    'b',  'n',  'm',  ',',  '.',  '/',  '\0', '\0', '\0', ' ',  '\0', '\0', '\0', '\0', '\0', '\0', // 63
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 79
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 95
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 111
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 127
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 143
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 159
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 175
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 191
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',  3  , '\0', '\0',  1  , '\0',  2  , '\0', '\0', // 207
     4  , '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 223
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 239
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', // 255
};

volatile bool keyPressed = FALSE;
volatile uint8_t key;

uint8_t get_char() {
    while (!keyPressed);
    keyPressed = FALSE;

    return key;
}

// _kbhit()
bool key_pressed() {
    return keyPressed;
}

void keyboard_handle_interrupt() {
    if (!IS_PREPARED_TO_READ()) {
        return;
    }

    uint8_t data = READ_DATA();

    // we can miss some keys :(
    key = key_map[data];

    if (key == '\0') {
        return;
    }

    keyPressed = TRUE;
}
