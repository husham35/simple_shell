#include "shell.h"

/**
 * wds_cnt - counts words in string
 * @str: string.
 * @delim_s: delimiters to separate the string.
 * @prt_arr: keeps words lenght.
 * Return: num of words counted.
 */

int wds_cnt(char *str, char *delim_s, unsigned int *prt_arr)
{
	unsigned int c, d, wd_len = 1, wd_count = 0;
	char *str_copy = str;
	bool start = false, delim;

	if (!str)
		return (0);
	while (!start)
		for (d = 0; delim_s[d]; d++)
		{
			if (*str_copy == delim_s[d])
				str_copy++;
			else
				start = true;
		}
	if (!*(str_copy + 1))
	{
		prt_arr[0] = 1;
		return (1);
	}
	for (c = 1; str_copy[c]; c++)
	{
		delim = chk_delim(str_copy[c], delim_s);
		if (delim && !(chk_delim(str_copy[c - 1], delim_s)))
		{
			prt_arr[wd_count] = wd_len;
			wd_count++;
		}
		if ((!str_copy[c + 1]) && !delim)
		{
			wd_len++;
			prt_arr[wd_count] = wd_len;
			wd_count++;
			break;
		}
		if (!delim)
			wd_len++;
		else
			wd_len = 0;
	}
	return (wd_count);
}
