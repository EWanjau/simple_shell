#include "shell.h"

/**
 * read_command - reads commands typed by the user
 * Return: the pointer to input string
 */
char *read_command(void)
{
	char buffer[1024];
	char *ptr = NULL;
	char ptrlen = 0;

	while (fgets(buffer, 1024, stdin))
	{
		int bufferlen = strlen(buffer);

		if (!ptr)
		{
			ptr = malloc(bufferlen + 1);
		}
		else 
		{
			char *ptr2 = realloc(ptr, ptrlen + bufferlen + 1);

			if (ptr2)
			{
				ptr = ptr2;
			}
			else 
			{
				free(ptr);
				ptr = NULL;
			}
		}
		if (!ptr)
		{
			fprintf(stderr, "error: emmory not allocated:%s", strerror(errno));
			return (NULL);
		}
		strcpy(ptr + ptrlen, buffer);

		if  (buffer[bufferlen - 1] == '\n')
		{
			if (bufferlen == 1 || buffer[bufferlen - 2] != '\\')
			{
				return (ptr);
			}
			ptr[ptrlen + bufferlen - 2] = '\0';
			bufferlen = bufferlen - 2;
			print_type2();
		}

		ptrlen = ptrlen + bufferlen;
	}
	return (ptr);
}
