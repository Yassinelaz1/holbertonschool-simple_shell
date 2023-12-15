#ifndef simple_shell
#define simple_shell

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void display_prompt(void);
void user_input(char **command);
void execute_command(char *command);

#endif