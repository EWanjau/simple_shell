#include "shell.h"

/**
 * unget_char - gets the last character from input
 * @src: input character
 * Returns: void
 */
void unget_char(struct source_s *src)
{
	if (src->charpos < 0)
		return;
	src->charpos--;
}

/**
 * next_char - gets the next character from input and updates the source pointer
 * @src: reads from input string
 * Return: next character read from input
 */
char next_char(struct source_s *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}

	char c1 = 0;
	if (src->charpos == INIT_SRC_POS)
		src->charpos = -1;
	else
		c1 = src->buffer[src->charpos];
	
	if (++src->charpos >= src->buffersize)
	{
		src->charpos = src->buffersize;
		return (EOF);
	}
	return (src->buffer[src->charpos]);
}

/**
 * peek_char - checks next character input
 * @src: input string
 * Return: the character checked
 */
char peek_char(struct source_s *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}

	long pos = src->charpos;
	if (pos == INIT_SRC_POS)
		pos++;
	pos++;

	if (pos >= src->buffersize)
		return (EOF);

	return (src->buffer[pos]);
}

/**
 * skip_white_spaces - skips whitespaces as a dilimiter
 * @src: input string command
 * Return: void
 */
void skip_white_spaces(struct source_s *src)
{
	char c;

	if (!src || !src->buffer)
	{
		return;
	}

	while (((c = peek_char(src)) != EOF) && (c == ' ' || c == '\t'))
	{
		next_char(src);
	}

}
