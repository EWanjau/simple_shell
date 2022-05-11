#include "shell.h"

/**
 * main - runs a continous loop
 * @argc: gets the argument count
 * @argv: gets the argument vecor
 * Return: exit
 */
int main(int argc, char **argv)
{
	char *command;

	do
	{
		print_type1();
		command = read_command();

		if (!command)
		{
			exit(EXIT_SUCCESS);
		}
		if (command[0] == '\0' || strcmp(command, "\n") == 0)
		{
			free(command);
			continue;
		}
		if (strcmp(command, "exit\n") == 0)
		{
			free(command);
			break;
		}
		printf("%s\n", command);

		free(command);
	} while(1);

	exit(EXIT_SUCCESS);
}
