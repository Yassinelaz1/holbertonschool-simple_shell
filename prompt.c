#include "shell.h"
/**
 *
 *
 *
 */
char *display_prompt(void)
{
    size_t size = 0;
    ssize_t r;
    char *buf = NULL;

    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "$ ", 2);
    r = getline(&buf, &size, stdin);
    if (r == -1)
    {
        free(buf);
        return NULL;
    }
    return (buf);
}

/**
 *
 *
 *
 */
char **split_line(char *line)
{
    char **command = NULL;
    char *token = NULL, *tmp = NULL;
    int compt = 0;
    int i = 0;

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

/**
 *
 *
 *
 */
int execute_command(char **command, char **argv, char **environ, int indx)
{
    char *fullcmd;
    int stat;
    pid_t child_pid;

    fullcmd = handle_path(command[0]);
    if (!fullcmd)
    {

        fprintf(stderr, "%s: %d: %s: not found\n", argv[0], indx, command[0]);
        freearray(command);
        return (127);
    }
    child_pid = fork();
    if (child_pid == 0)
    {
        if (execve(fullcmd, command, environ) == -1)
        {

            free(fullcmd);
            fullcmd = NULL;
            freearray(command);
        }
    }
    else
    {
        waitpid(child_pid, &stat, 0);
        freearray(command);
        free(fullcmd);
        fullcmd = NULL;
    }
    return (WEXITSTATUS(stat));
}
