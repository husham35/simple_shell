#include "shell.h"
/**
 * chk_chained - checks if current char in buffer is a chained delimeter
 * @info: struct
 * @b: char buffer
 * @ptr: addr of current position in buf
 * Return: 1 if delimeter is chain, else 0
 */
bool chk_chained(ss_info *info, char *b, size_t *ptr)
{
	size_t j = *ptr;

	if (b[j] == '|' && b[j + 1] == '|')
	{
		b[j] = 0;
		j++;
		info->cmd_buf_kind = ORFLAG;
	}
	else if (b[j] == '&' && b[j + 1] == '&')
	{
		b[j] = 0;
		j++;
		info->cmd_buf_kind = ANDFLAG;
	}
	else if (b[j] == ';')
	{
		b[j] = 0;
		info->cmd_buf_kind = CHFLAG;
	}
	else
		return (false);
	*ptr = j;
	return (true);
}

/**
 * chk_chn - checks to continue chaining
 * @info: struct
 * @b: char buffer
 * @ptr: addr of index  in buffer
 * @i: starting position in buffer
 * @l: length of buffer
 * Return: void
 */
void chk_chn(ss_info *info, char *b, size_t *ptr, size_t i, size_t l)
{
	size_t j = *ptr;

	if (info->cmd_buf_kind == ANDFLAG)
	{
		if (info->status)
		{
			b[i] = 0;
			j = l;
		}
	}
	if (info->cmd_buf_kind == ORFLAG)
	{
		if (!info->status)
		{
			b[i] = 0;
			j = l;
		}
	}
	*ptr = j;
}

/**
 * change_v - replaces vars in the tokenized string
 * @info: struct
 * Return: 1 if replaced, 0 otherwise
 */
int change_v(ss_info *info)
{
	list_str *node;

	for (int i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!c_str_cmp(info->argv[i], "$?"))
		{
			str_alter(&(info->argv[i]),
					  _str_dup(alter_base(info->status, 10, 0)));

			continue;
		}
		if (!c_str_cmp(info->argv[i], "$$"))
		{
			str_alter(&(info->argv[i]),
					  _str_dup(alter_base(getpid(), 10, 0)));

			continue;
		}
		node = nd_s_bg(info->env, &info->argv[i][1], '=');
		if (node)
		{
			str_alter(&(info->argv[i]),
					  _str_dup(_str_chr(node->str, '=') + 1));

			continue;
		}
		str_alter(&info->argv[i], _str_dup(""));
	}
	return (0);
}
/**
 * str_alter - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int str_alter(char **old, char *new)
{
	free(*old);
	*old = new;

	return (1);
}
