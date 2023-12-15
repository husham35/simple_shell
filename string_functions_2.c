#include "shell.h"

/**
 * _str_cpy - make a copy of a string
 * @d: destination string
 * @s: source string
 * Return: addr to destination string
 */
char *_str_cpy(char *d, char *s)
{
	int i = 0;

	if (d == s || s == 0)
		return (d);
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = 0;
	return (d);
}

/**
 * _str_dup - makes a duplicate of a string
 * @s: input string to duplicate
 * Return: adddr to duplicated string
 */
char *_str_dup(const char *s)
{
	int len = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	for (len++; len--;)
		r[len] = *--s;
	return (r);
}

/**
 * _puts - prints a string
 * @s: string to be printed
 * Return: Nothing
 */

void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		c_put_char(s[i]);
		i++;
	}
}

/**
 * c_put_char - prints the character to STDOUT
 * @c: char to print
 * Return: 1 on success, else -1 is with and errno
 */
int c_put_char(char c)
{
	static int i;
	static char buf[BUFFWRSIZE];

	if (c == ERRFLUSH || i >= BUFFWRSIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != ERRFLUSH)
		buf[i++] = c;
	return (1);
}
