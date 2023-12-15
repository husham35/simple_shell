#include "shell.h"

/**
 * c_str_len - finds the length of a string
 * @str: input string
 * Return: length of string
 */
int c_str_len(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * c_str_cmp - performs lexicogarphic comparison of two strangs.
 * @s1: first string
 * @s2: second string
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int c_str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * chk_prefix - check for a prefix in string
 * @hay_stack: string to search
 * @ndl: substring to find
 * Return: address of haystack, else NULL
 */
char *chk_prefix(const char *hay_stack, const char *ndl)
{
	while (*ndl)
		if (*ndl++ != *hay_stack++)
			return (NULL);
	return ((char *)hay_stack);
}

/**
 * _str_cat - concatenates two strings
 * @d: destination buffer
 * @s: source buffer
 * Return: pointer to destination buffer
 */
char *_str_cat(char *d, char *s)
{
	char *result = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (result);
}
