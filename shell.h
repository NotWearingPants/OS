#include "common.h"

void start_shell();
void handle_command(char* command, uint8_t length_command);
bool check_write_syntax(char* command);
int shell_input(uint8_t pos_x, uint8_t pos_y, char* buffer);