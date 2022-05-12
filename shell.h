#ifndef SHELL_H
#define SHELL_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"

/*for the scanner part*/
#define EOF (-1)
#define ERRCHAR (0)
#define INIT_SRC_POS (-2)

/*command prompt loop at the beginning*/

void print_type1(void);
void print_type2(void);

/*read the input by the user*/

char *read_command(void);

/*get the input to the scanner*/

struct source_s
{
	char *buffer;		/*the input commands by reader*/
	long buffersize;	/*size of the text input*/
	long charpos;		/*the char position from source text*/
};

/*functions to help read characters one at a time*/

char next_char(struct source_s *src);
void unget_char(struct source_s *src);
char peek_char(struct source_s *src);
void skip_white_spaces(struct source_s *src);

/*parsing the input strings in small tokens*/

struct token_s
{
	struct source_s *src;		/*input source (commands from cli)*/
	int text_len;			/*length of token*/
	char *text;			/*the token text*/
};

/*indicate the end of input*/

extern struct token_s eof_token;

/*captures and handles the tokens*/

struct token_s *tokenize(struct source_s *src);
void free_token(struct token_s *tok);

#endif
