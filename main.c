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
		struct source_s src;
		src.buffer   = command;
		src.buffersize  = strlen(command);
		src.charpos   = INIT_SRC_POS;
		parse_and_execute(&src);
		
		free(command);
	} while(1);

	exit(EXIT_SUCCESS);
}

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

int parse_and_execute(struct source_s *src)
{
    skip_white_spaces(src);

    struct token_s *tok = tokenize(src);

    if(tok == &eof_token)
    {
        return 0;
    }

    while(tok && tok != &eof_token)
    {
        struct node_s *cmd = parse_simple_command(tok);

        if(!cmd)
        {
            break;
        }

        do_simple_command(cmd);
        free_node_tree(cmd);
        tok = tokenize(src);
    }

    return 1;
}
