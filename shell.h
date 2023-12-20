#ifndef simple_shell
#define simple_shell

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define DELIM " \t\n"

char *display_prompt(void);
char **split_line(char *line);
int execute_command(char **command, char **argv, char **env);

#endif