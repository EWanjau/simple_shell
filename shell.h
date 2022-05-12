#ifndef SHELL_H
#define SHELL_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"
#include "unistd.h"
#include "sys/stat.h"
#include "sys/wait.h"

/*for the scanner part*/
#define EOF (-1)
#define ERRCHAR (0)
#define INIT_SRC_POS (-2)

/*command prompt loop at the beginning*/

void print_type1(void);
void print_type2(void);

/*read the input by the user*/

char *read_command();

/*____________________SCANNER PART____________________________________*/

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

/*_______________________PARSER______________________*/

struct node_s *parse_simple_command(struct token_s *tok);

/*_______________________Structure of Nodes to feed the executor_________________________*/

enum node_type_e
{
	NODE_COMMAND,	/*sample command*/
	NODE_VAR,	/*name of variable*/
};

enum val_type_e
{
	VAL_SINT = 1,
	VAL_UINT,
	VAL_SLLONG,
	VAL_ULLONG,
	VAL_FLOAT,
	VAL_LDOUBLE,
	VAL_CHR,
	VAL_STR,	
};

union symval_u
{
	long		sint;
	unsigned long 	uint;
	long long	sllong;
	unsigned long long ullong;
	double 		sfloat;
	long double 	ldouble;
	char 		chr;
	char 		*str;
};

struct node_s
{
	enum node_type_e type;
	enum val_type_e val_type;
	union symval_u val;
	int children;
	struct node_s *first_child;
	struct node_s *next_sib, *prev_sib;
};

struct node_s *new_node(enum node_type_e type);
void add_child_node(struct node_s *parent, struct node_s *child);
void free_node_tree(struct node_s *node);
void set_node_val_str(struct node_s *node, char *val);

/*_________Executor__________*/

char *search_path(char *file);
int do_exec_cmd(int argc, char **argv);
int do_simple_command(struct node_s *node);
int parse_and_execute(struct source_s *src);

#endif
