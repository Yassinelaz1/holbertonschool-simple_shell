#include "shell.h"
int main(int argc, char **argv, char **env)
{
    char *line = NULL;
    char **command = NULL;
    int stat;
     
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
        command = split_line(line);

        stat = execute_command(command, argv, env);
        
    }
    return (stat);
}
