#include "shell.h"
void freearray(char **command)
{
	int i;

	if (!command)
		return;

	for (i = 0; command[i]; i++)
		free(command[i]), command[i] = NULL;
	free(command), command = NULL;
}