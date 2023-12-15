#include "shell.h"

/**
**_str_n_cpy - copies n bytes of string
*@d: resulting copied string
*@s: source string to copy from
*@n: number of bytes of characters to be copied
*Return: copied string
*/
char *_str_n_cpy(char *d, char *s, int n)
{
	int i, j;
	char *r = d;

	i = 0;
	while (s[i] != '\0' && i < n - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (r);
}

/**
**_str_n_cat - concatenates two strings by a number of bytes
*@d: first string
*@s: second string
*@n: max number of bytes to be used
*Return: the concatenated string
*/
char *_str_n_cat(char *d, char *s, int n)
{
	int i, j;
	char *r = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (s[j] != '\0' && j < n)
	{
		d[i] = s[j];
		i++;
		j++;
	}
	if (j < n)
		d[i] = '\0';
	return (r);
}

/**
**_str_chr - finds a character in a string
*@s: parsed string
*@c: character to find in string
*Return: pointer to s if successful, else NULL
*/
char *_str_chr(char *s, char c)
{
	do
	{
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
