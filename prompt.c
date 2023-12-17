#include "shell.h"
void display_prompt(void)
{
    printf("$ ");
}

void user_input(char **command)
{
    size_t size = 0;

    if (getline(command, &size, stdin) == -1)
    {
        if (*command == NULL)
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }

    (*command)[strcspn(*command, "\n")] = '\0'; /* Remove newline */
}

void execute_command(char *command)
{
    pid_t child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child_pid == 0)
    {
        /* Child process */
        char *token = strtok(command, " ");
        char **args = (char **)malloc(2 * sizeof(char *));
        int i = 0;
		int j;

        while (token != NULL)
        {
            args[i++] = strdup(token);
            token = strtok(NULL, " ");
        }

        args[i] = NULL; /* Null-terminate the argument list */

        execvp(args[0], args);
        perror("$");

        /* Free allocated memory in the child process */
        for (j = 0; args[j] != NULL; ++j)
        {
            free(args[j]);
        }
        free(args);

        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        int status;
        if (waitpid(child_pid, &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}