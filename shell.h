#ifndef simple_shell
#define simple_shell

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

#define DELIM " \t\n"
extern char **environ;

void freearray(char **command);

char *display_prompt(void);
char **split_line(char *line);
int execute_command(char **command, char **argv, char **environ , int indx);

char *_getenv(char *variable);
char *handle_path(char *command);

int is_built_in(char **command);
void handle_built_in(char **command, int *status);
void hsh_exit(char **cmd, int *status);
void hsh_env(char **cmd, int *status);
#endif