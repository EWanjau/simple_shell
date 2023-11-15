#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <stdarg.h>
#include <limits.h>
#ifndef BUFF_SIZE
#define BUFF_SIZE 300
#endif
/**
 * struct link - node that contains the directories
 * @dir: directory
 * @next: position to change the node
 */
typedef struct link
{char *dir;
struct link *next;
} link_t;
/**
* struct formats - struct formats
* @ch: pointer to firts element.
* @func: The function associated.
*/
typedef struct formats
	{
		char *ch;
		int (*func)();
	} form;

char *execute_command(char *argm);
int _putchar(char c);
int _printf(const char *format, ...);
int p_aux_int(long int n, long int);
int p_str(va_list arguments);
int p_char(va_list arguments);
int p_int(va_list arguments);
extern char **environ;
char *_getenv(const char *name);
char *_strcpy(char *dest, char *src);
char *_strtok(char *str, char *delim);
ssize_t _getline(char **bufline, size_t *size, FILE *std);
char **splitline(char *command_line);
void signal_c(int sign);
int _myexit(char *line);
int _strlen(char *s);
int execute_process(char **argm, char **argv, int counter);
link_t *_add_nodeint_end(link_t **head, char *n);
size_t _print_listint(link_t *h);
link_t *_link(char *a);
char *_strcat(char *directory, char *slash, char *arg);
char *_which(link_t **head, char *av);
void free_list(link_t *head);
char *check_path(char *argm);
int _myenv(char *line, int counter, char **argv, char **env);
int _getchar(void);

#endif
