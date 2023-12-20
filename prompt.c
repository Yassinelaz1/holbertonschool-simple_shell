#include "shell.h"
char *display_prompt(void)
{
    size_t size = 0;
    int r;

    char *buf;
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "$ ", 2);
    r = getline(&buf, &size, stdin);
    if (r == -1)
    {
        free(buf);
        exit(EXIT_SUCCESS);
    }
    return (buf);
}

char **split_line(char *line)
{
    char **command = NULL;
    char *token = NULL, *tmp = NULL;
    int compt = 0;

    if (!line)
        return (NULL);
    tmp = strdup(line);
    token = strtok(tmp, DELIM);
    if (!token)
    {
        free(line), line = NULL;
        free(tmp), tmp = NULL;
        return (NULL);
    }

    while (token)
    {
        compt++;
        token = strtok(NULL, DELIM);
    }
    free(tmp), tmp = NULL;
    command = malloc(sizeof(char *) * (compt + 1));
    if (!command)
    {
        free(line);
        line = NULL;
        return (NULL);
    }

    token = strtok(line, DELIM);
    while (token)
    {
        command[i] = strdup(token);
        token = strtok(NULL, DELIM);
        i++;
    }
    free(line), line = NULL;
    command[i] = NULL;
    return (command);
}

int execute_command(char **command, char **argv, char **env)
{
    pid_t child_pid = fork();
    int stat;
    int i;

    if (child_pid == 0)
    {
        if (execve(command[0], command, env) == -1)
        {
            perror(argv[0]);
            exit(127);
        }
    }

    else
    {
        waitpid(child_pid, &stat, 0);
    }
    return (1);
}
