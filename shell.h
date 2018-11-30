#include "common.h"

void start_shell();
void handle_command(char* command, uint8_t length_command);
bool check_write_syntax(char* command);
char* ixtract_argv(char* string, int* arr, int argv_num);
