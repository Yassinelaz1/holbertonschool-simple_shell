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
        command = split_line(line);
        /*for ( i = 0; command[i]; i++)
        {
            printf("%s\n", command[i]);
            free(command[i]), command[i]=NULL;
        }
        free(command);*/
        stat = execute_command(command, argv, env);
       
    }
     return (stat);
}
