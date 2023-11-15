#include "shell.h"
/**
 * check_path - check if argumnt is already a path
 * @argm: entry argument
 * Return: argm (Success) NULL (Not found)
 */
char *check_path(char *argm)
{
	if (access(argm, X_OK) == 0)
		return (argm);
	return (NULL);
}

/**
 * execute_command - check if argumnt is already a path
 * @argm: entry argument
 * Return: argm (Success) NULL (Not found)
 */
char *execute_command(char *argm)
{
	char *path = NULL;
	link_t *head = NULL;
	char *buffer = NULL;

	path = _getenv("PATH");
	head = _link(path);
	buffer = _which(&head, argm);
	if (buffer != NULL)
	{
		free(path),
		free_list(head);
		return (buffer);
	}
	free(path);
	free_list(head);
	return (NULL);
}
