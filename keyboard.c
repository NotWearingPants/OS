#include "keyboard.h"
#include "common.h"
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

const uint8_t key_map[] = {
    '\0', '\0', '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',  '-',  '=',  '\0', '\0',
    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p',  '[',  ']',  '\n', '\0', 'a',  's',
    'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',  '\0', '\0', '\0', '\0', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  '\0', '\0', '\0', ' ',  '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
    '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',
};

// volatile bool enterPressed = FALSE;
volatile bool keyPressed = FALSE;
uint8_t key;

char get_char() {
    while (!keyPressed);
    keyPressed = FALSE;

    return key;
}

void keyboard_handle_interrupt() {
    if (!IS_PREPARED_TO_READ()) {
        return;
    }

    uint8_t data = READ_DATA();

    key = key_map[data];

    if (key == '\0') {
        return;
    }
    else {
        keyPressed = TRUE;
    }

    // shell_handle_key(key);
}
