#include "shell.h"
int main(int argc, char **argv, char **env)
{
    char *line = NULL;
    char **command = NULL;
    int stat;
        int i;
    (void)argc;


    while (1)
    {
        line = display_prompt();
        command = split_line(line);

        stat = execute_command(command, argv, env);
        for ( i = 0; command[i]; i++)
        {
            free(command[i]);
            command[i] = NULL;
        }
        free(command);
    }
    return (stat);
}
