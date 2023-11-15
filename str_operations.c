#include "shell.h"
/**
 * _strlen - find the length of a string
 * @s: entry string
 * Return: number of bytes
 **/
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i]; i++)
	{
	}
	return (i);
}
/**
 * _strcat - concatenate directories with the 1st position of the array
 * @directory: directories
 * @slash: /
 * @arg: array of commands.
 * Return: str
 **/
char *_strcat(char *directory, char *slash, char *arg)
{
	char *str = NULL;
	int l1, l2, i, k;

	l1 = _strlen(directory);
	l2 = _strlen(arg);
	str = malloc(sizeof(char) * (l1 + l2 + 2));
	if (!str)
		return (NULL);
	for (i = 0; directory[i]; i++)
		str[i] = directory[i];
	str[i] = *slash;
	k = i + 1;
	for (i = 0; arg[i]; i++)
		str[k + i] = arg[i];
	str[k + i] = '\0';
	return (str);
}
/**
 * _strtok - breaks a string into a sequence
 * @str: string
 * @delim: specific character to break the string
 * Return: NULL if fails or pointer to divided string.
 */
char *_strtok(char *str, char *delim)
{
	int i = 0, j = 0, a = 0;
	static char *tracker;

	if (!delim || (!str && !tracker))
		return (NULL);
	str == NULL ? str = tracker : str;
	for (; str[j] == ' ' ; j++)
	{
		if (str[j + 1] == '\0')
			return (NULL);
	}
	for (i = j ; str[i] != '\0' ; i++)
	{
		if (str[i] == *delim)
		{
			a = 1;
			break;
		}
	}
	for (; str[i] != '\0' ; i++)
		if (str[i] != delim[0])
			break;
		else if (str[i + 1] == '\0')
		{
			a = 0, str[i] = '\0';
			break;
		}
		else
			str[i] = '\0';
	if (a == 0)
	{
		tracker = NULL;
		return (str + j);
	}
	if (str + i)
		tracker = str + i;
	else
		tracker = NULL;
	return (str + j);
}
/**
 * *_strcpy - copies the string pointed to another pointer
 * @src: original pointer
 * @dest: destination pointer
 * Return: return a pointer char
 */
char *_strcpy(char *dest, char *src)
{
	int a, b;

	for (a = 0; src[a] != '\0' ; a++)
	{
	}
	for (b = 0; b < a ; b++)
	{
		dest[b] = src[b];
	}
	for (; b <= a ; b++)
	{
		dest[b] = '\0';
	}
	return (dest);
}
