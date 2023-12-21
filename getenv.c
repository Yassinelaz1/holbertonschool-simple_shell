#include "shell.h"

char *_getenv(char *variable)
{
	char *tmp,*key,*val,*env;
	int i;

	for (i = 0; environ[i]; i++)
	{
		tmp = strdup(environ[i]);
		key = strtok(tmp,"=");

		if (key != NULL && strcmp(key, variable) == 0)
		{
			val = strtok(NULL, "\n");
			env = strdup(val);
			free(tmp);
			return (env);
		}

		free(tmp), tmp = NULL;
	}

	return (NULL);
}
