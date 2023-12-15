#include "shell.h"
/**
 * puts_err - prints string to STDOUT
 * @str: string to printed
 */
void puts_err(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		put_char_err(str[i]);
		i++;
	}
}
/**
 * put_char_err - prints character to STDERR
 * @c: character to print
 * Return: 1 on success, else -1
 */
int put_char_err(char c)
{
	static int i;
	static char buf[BUFFWRSIZE];

	if (c == ERRFLUSH || i >= BUFFWRSIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != ERRFLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * w_char - writes character to file descriptor
 * @c: character to print
 * @fd: file descriptor to write to
 * Return: 1 on success, else -1
 */
int w_char(char c, int fd)
{
	static int i;
	static char buf[BUFFWRSIZE];

	if (c == ERRFLUSH || i >= BUFFWRSIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != ERRFLUSH)
		buf[i++] = c;
	return (1);
}
/**
 * w_chars - write an input string
 * @s: the string to be printed
 * @fd: file descriptor to write to
 * Return: number of chars written
 */
int w_chars(char *s, int fd)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += w_char(*s++, fd);
	}
	return (i);
}
