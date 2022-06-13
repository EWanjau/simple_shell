#include "simple.h"

/*THIS IS TASK 1 SIMPLE SHELL PROJECT*/


int main(void)
{
	char **token;
	char *line;
	int status;

	while (status)
	{
		write(1, "$", 1);
		
		line = readline ();
		token = splitline(line);
		status = execute(token);

		free(line);
		free(token);
		/*write (1, buffer, _strlen(buffer));*/
	}
	return (0);
}	

int _strlen(char *str)
{
	int len;

	if (!str)
		return (0);

	for (len = 0; str[len] != '\0'; len++)
		;
	
	return (len);
}

int execute(char **arg)
{
	int i;
	char *b_str[] = {"cd", "exit"};
	int (*b_func[])(char **) = {&c_d, &ex_it};

	if (arg[0] == NULL)
		return (1);
	for (i = 0; i < builtins(); i++)
	{
		if (_strcmp(arg[0], b_str[i]) == 0)
		{
			return ((*b_func[i])(arg));
		}

	}
	return (launch(arg));

}
int builtins(void)
{
	char *b_str[] = {"cd", "exit"};

	return (sizeof(b_str) / sizeof(char *));

}
int c_d(char **arg)
{
	if (arg[1]== NULL)
	{
		perror("Missing Arguments\n");
	}
	else
	{
		if (chdir(arg[1]) != 0)
			perror("Error");

	}
	return (1);
}

int ex_it(__attribute__((unused))char **arg)
{
	return (0);
}

int launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Execution Failed\n");
			return (-1);
		}


	}
	else if (pid < 0)
	{
		perror("Child Process Not Created\n");
		return (-1);
	}
	else
	{
		do{
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (wpid);

}
#define BUFFSIZE 64

char **splitline(char *str)
{
	int postn = 0;
	int buffsize = BUFFSIZE;
	char delim[] = " \t\n";
	char **tokens = malloc(sizeof(char *) * buffsize);
	char *tkn;

	if (!tokens)
	{
		perror("Memory Allocation Error\n");
		return (NULL);
	}
	
	tkn = strtok(str, delim);

	while (tkn != NULL)
	{
		tokens[postn] = tkn;
		postn++;
		if (postn >= buffsize)
		{
			buffsize += BUFFSIZE;
			tokens = realloc(tokens, buffsize * sizeof(char *));
			if (!tokens)
			{
				perror("Memmory Not Allocated");
				return (NULL);
			}
		}
		tkn = strtok(NULL, delim);
	}
	tokens[postn] = NULL;

	return (tokens);
}

char *readline(void)
{
	char *buffer = NULL;
	size_t n = 0;

	if (getline(&buffer, &n, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("Readline Error");
			exit(EXIT_FAILURE);
		}
	}
	return (buffer);
}
int _strcmp(char *s1, char *s2)
{
	int i;

	if (_strlen(s1) != _strlen(s2))
		return (-1);
	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}
	return (0);
}
