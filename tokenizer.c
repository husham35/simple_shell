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
	int v, no_of_words;
	char **words, *str_ptr = str;
	unsigned int c, word_sizes[MAXWDCOUNT];

	mk_zeroes(word_sizes, MAXWDCOUNT);
	no_of_words = wds_cnt(str, delims, word_sizes);
	if (no_of_words == 0)
		return (NULL);
	words = malloc((sizeof(char *) * no_of_words) + 1);
	if (!words)
		return (NULL);
	for (v = 0; v < no_of_words; v++)
	{
		words[v] = malloc((sizeof(char) * word_sizes[v]) + 1);
		if (!words[v])
		{
			for (v--; v >= 0; v--)
				free(words[v]);
			free(words);
			return (NULL);
		}
		for (c = 0; c < word_sizes[v]; c++, str_ptr++)
		{
			while (chk_delim(*str_ptr, delims))
				str_ptr++;
			words[v][c] = *str_ptr;
		};
		words[v][c] = '\0';
	}
	*num_w = no_of_words;
	words[v] = NULL;
	return (words);
}

/**
 * **str_to_words - tokenizes a string into words ignoring repeated delimiters
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
		if (!chk_delim(str[i], delim) && (chk_delim(str[i + 1], delim) || !str[i + 1]))
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
