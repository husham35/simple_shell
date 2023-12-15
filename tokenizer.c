#include "shell.h"

/**
 * expld_str - tokenizes a string into words
 * @str: parsed string.
 * @delims: delimiters to split the string by.
 * @num_w: number of words in the string
 * Return: vector of pointers to strings (words).
 */

char **expld_str(char *str, char *delims, size_t *num_w)
{
	int vec, num_wds;
	char **words, *str_ptr = str;
	unsigned int c, wd_size[MAXWDCOUNT];

	mk_zeroes(wd_size, MAXWDCOUNT);
	num_wds = wds_cnt(str, delims, wd_size);
	if (num_wds == 0)
		return (NULL);
	words = malloc((sizeof(char *) * num_wds) + 1);
	if (!words)
		return (NULL);
	for (vec = 0; vec < num_wds; vec++)
	{
		words[vec] = malloc((sizeof(char) * wd_size[vec]) + 1);
		if (!words[vec])
		{
			for (vec--; vec >= 0; vec--)
				free(words[vec]);
			free(words);
			return (NULL);
		}
		for (c = 0; c < wd_size[vec]; c++, str_ptr++)
		{
			while (chk_delim(*str_ptr, delims))
				str_ptr++;
			words[vec][c] = *str_ptr;
		};
		words[vec][c] = '\0';
	}
	*num_w = num_wds;
	words[vec] = NULL;
	return (words);
}

/**
 * **str_to_words - tokenizes a string into words
 * avoiding repeated delimiters
 * @str: parsed string
 * @delim: delimeter
 * Return: a pointer to an array of strings, else NULL
 */
char **str_to_words(char *str, char *delim)
{
	int i, j, k, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!chk_delim(str[i], delim) && (chk_delim(str[i + 1], delim)
					|| !str[i + 1]))
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (chk_delim(str[i], delim))
			i++;
		k = 0;
		while (!chk_delim(str[i + k], delim) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
