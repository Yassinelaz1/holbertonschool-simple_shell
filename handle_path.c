
#include "shell.h"

char *handle_path(char *command)
{
	char *path_env, *fullcmd, *path;
	int i;
	struct stat buf;
	for (i = 0; command[i]; i++)
	{
		if (command[i] == '/')
		{
			if (stat(command, &buf) == 0)
				return strdup(command);

			return NULL;
		}
	}
	path_env = _getenv("PATH");
	path = strtok(path_env, ":");
	while (path)
	{
		fullcmd = malloc(strlen(path) + strlen(command) + 2);

		if (fullcmd != NULL)
		{
			strcpy(fullcmd, path);
			strcat(fullcmd, "/");
			strcat(fullcmd, command);

			if (stat(fullcmd, &buf) == 0)
			{
				free(path_env);
				return fullcmd;
			}

			free(fullcmd);

			path = strtok(NULL, ":");
		}
		else
		{
			free(path_env);
			return NULL;
		}
	}
	free(path_env);
	return NULL;
}
