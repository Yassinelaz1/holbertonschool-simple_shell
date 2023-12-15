#include "shell.h"
int main(void) 
{
	char *command = NULL; /*command = null*/
	while (1)/*main loop */
	{
		display_prompt();
		user_input(&command);
		execute_command(command);
		free(command);
	}
	return 0;
}

void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		printf("$ ");
	}
}

void user_input(char **command)
{
	size_t size = 0;

	if (getline(command, &size, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	(*command)[strcspn(*command, "\n")] = '\0'; /*Remove newline*/
	free(command);
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
		/* filston process*/
		char *token = strtok(command, " ");
		char **args = (char **)malloc(2 * sizeof(char *));
		int i= 0;
		int j ;

		while (token != NULL)
		{
			args[i++] = strdup(token);
			token = strtok(NULL, " ");
		}

		args[i] = NULL; /*Null-terminate the argument list*/

		execve(args[0], args, NULL);
		perror("$");

		/*Free allocated memory in the filston process*/
		for (j = 0; args[j] != NULL; ++j)
		{
			free(args[j]);
		}
		free(args);

		exit(EXIT_FAILURE);
	}
	else
	{
		/*Papa process*/
		int status;
		waitpid(child_pid, &status, 0);
	}
}
