#include "shell.h"

char *tok_buffer = NULL;
int tok_buffersize = 0;
int tok_bufferindex = -1;

/*indicate end of input token*/
struct token_s eof_token =
{
	.text_len = 0
};
/**
 * add_to_buffer(char c) - adds a character to the buffer
 * @c: the character to add
 * Return: void
 */
void add_to_buffer(char c)
{
	tok_buffer[tok_bufferindex++] = c;

	if (tok_bufferindex >= tok_buffersize)
	{
		char *tmp = realloc(tok_buffer, tok_buffersize * 2);

		if (!tmp)
		{
			errno = ENOMEM;
			return;
		}
		tok_buffer = tmp;
		tok_buffersize = tok_buffersize * 2;
	}
}

/**
 * create_token - converts a string to a token structure
 * @str: input string
 * Return: token structure
 */
struct token_s *create_token(char *str)
{
	struct token_s *tok = malloc(sizeof(struct token_s));

	if (!tok)
	{
		return (NULL);
	}

	memset(tok, 0, sizeof(struct token_s));
	tok->text_len = strlen(str);

	char *nstr = malloc(tok->text_len + 1);

	if (!nstr)
	{
		free(tok);
		return (NULL);
	}

	strcpy(nstr, str);
	tok->text = nstr;

	return (tok);
}

/**
 * free_token - frees memory and text occupied by token structure
 * @tok: token to be freed
 * Return: void
 */
void free_token(struct token_s *tok)
{
	if (tok->text)
	{
		free(tok->text);
	}
	free(tok);
}

/**
 * tokenize - converts source string to tokens by calling functions
 * @src: source string
 * Return: tokens
 */
struct token_s *tokenize(struct source_s *src)
{
	int endloop = 0;

	if (!src || !src->buffer || !src->buffersize)
	{
		errno = ENODATA;
		return (&eof_token);
	}

	if (!tok_buffer)
	{
		tok_buffersize = 1024;
		tok_buffer = malloc(tok_buffersize);
		if (!tok_buffer)
		{
			errno = ENOMEM;
			return (&eof_token);
		}
	}

	tok_bufferindex = 0;
	tok_buffer[0] = '\0';

	char nc = next_char(src);

	if (nc == ERRCHAR || nc == EOF)
	{
		return (&eof_token);
	}

	do
	{
		switch (nc)
		{
			case ' ':
			case '\t':
				if (tok_bufferindex > 0)
				{
					endloop = 1;
				}
				break;
			case '\n':
				if (tok_bufferindex > 0)
				{
					unget_char(src);
				}
				else
				{
					add_to_buffer(nc);
				}
				endloop = 1;
				break;

			default:
				add_to_buffer(nc);
				break;
			}
		if (endloop)
		{
			break;
		}

		} while ((nc = next_char(src)) != EOF);

	if (tok_bufferindex == 0)
	{
		return (&eof_token);
	}

	if (tok_bufferindex >= tok_buffersize)
	{
		tok_bufferindex--;
	}

	tok_buffer[tok_bufferindex] = '\0';

	struct token_s *tok = create_token(tok_buffer);

	if (!tok)
	{
		fprintf(stderr, "error: failed to allocate memory: %s\n", strerror(errno));
		return (&eof_token);
	}
	
	tok->src = src;
	return (tok);
}
