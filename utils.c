#include "shell.h"

/**
 * frm_trm - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if frm_trm mode else 0
 */

int frm_trm(ss_info *info)
{
	return (isatty(STDIN_FILENO) && info->fd_rd <= 2);
}

/**
 * c_is_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic else 0 if not
 */

int c_is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * c_al_to_in - transforms a string to an integer
 * @s: string to transform
 * Return: transformed int, else 0 if no numbers in string
 */

int c_al_to_in(char *s)
{
	int i, sign = 1, flg = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flg != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flg = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

/**
 * chk_delim - verifies if a char is a delimiter
 * @c: char to checked.
 * @delims: list of chars to be compared
 * Return: true if a delimiter, else false.
 */

bool chk_delim(char c, char *delims)
{
	int s;

	for (s = 0; delims[s]; s++)
		if (c == delims[s])
			return (true);
	return (false);
}
