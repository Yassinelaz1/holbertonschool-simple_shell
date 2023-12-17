#include "shell.h"
int main(void) 
{
    char *command = NULL;
    while (1)
    {
        display_prompt();
        user_input(&command);
        if (!command)
        {
            continue;
        }
        execute_command(command);
        free(command);
    }
    return 0;
}