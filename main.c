#include "shell.h"
int main(int argc, char **argv, char **environ)
{
    char *line = NULL;
    char **command = NULL;
    int stat;
    int indx = 0;

    (void)argc;

    while (1)
    {
        line = display_prompt();
        if (line == NULL)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            return (stat);
        }
        indx++;
        command = split_line(line);
        if (!command)
            continue;
        stat = execute_command(command, argv, environ,indx);
    }
    return (stat);
}
