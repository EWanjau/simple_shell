#include "shell.h"
/**
 * main - Entry point for shell
 * @argc: Number of arguments
 * @argv: string of arguments
 * @env: enviromet variable
 * Return: 0 (Return value)
 */
int main(int __attribute__((unused))argc, char **argv, char **env)
{
	int status_output = 0, read = 1, counter = 0;

	while (read)
	{
		char *command_line = NULL, **argm = NULL;
		size_t line_size = 0;

		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#myshell$ ", 10);
		signal(SIGINT, signal_c);
		read = getline(&command_line, &line_size, stdin);
		if (read < 0)
		{
			free(command_line);
			exit(status_output);
		}
		if (read == 1)
		{
			free(command_line);
			continue;
		}
		if (read != EOF)
		{
			counter++;
			_strtok(command_line, "\n");
			if (_myexit(command_line) == 0)
				return (status_output);
			if (_myenv(command_line, counter, argv, env) == 0)
				continue;
			argm = splitline(command_line);
			if (argm[0] == NULL)
			{
				free(command_line), free(argm);
				continue;
			}
			status_output = execute_process(argm, argv, counter);
		}
		free(command_line), free(argm);
	}
	return (status_output);
}
