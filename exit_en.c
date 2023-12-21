#include "shell.h"

int is_built_in(char **command)

{
	char *built[] = {"exit", "env", NULL};
	int i;

	for (i = 0; built[i]; i++)
	{
		if (strcmp(command[0], built[i]) == 0)
		{
			return (1);
		}
	}
	return (0);

}

void handle_built_in(char **command, int *stat)

{
	if (strcmp(command[0], "exit") == 0)
	{
		hsh_exit(command, stat);
	}
	else if (strcmp(command[0], "env") == 0)
	{
		hsh_env(command, stat);
	}
}

void hsh_exit(char **cmd, int *stat)

{
	freearray(cmd);
	exit(*stat);
}

void hsh_env(char **cmd, int *stat)

{
	int i;

	for (i = 0; environ[i]; i++)
	{
		printf("%s\n", environ[i]);
	}
	freearray(cmd);
	(*stat) = 0;
}