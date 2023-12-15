#include "shell.h"

/**
 * unset_alias - unsets alias
 * @info: struct
 * @s: the alias
 * Return: always 0 on success, 1 on error
 */
int unset_alias(ss_info *info, char *s)
{
	char *ptr, c;
	int ret;

	ptr = _str_chr(s, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	ret = del_node(&(info->alias),
				   gt_nd_ind(info->alias, nd_s_bg(info->alias, s, -1)));
	*ptr = c;
	return (ret);
}

/**
 * set_alias - sets string
 * @info: struct
 * @s: alias
 * Return: always 0 on success, else 1 on error
 */
int set_alias(ss_info *info, char *s)
{
	char *ptr;

	ptr = _str_chr(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, s));

	unset_alias(info, s);
	return (ins_nd_en(&(info->alias), s, 0) == NULL);
}

/**
 * print_alias - prints an alias
 * @node: alias
 * Return: always 0 on success, 1 on error
 */
int print_alias(list_str *node)
{
	char *ptr = NULL, *alias_str = NULL;

	if (node)
	{
		ptr = _str_chr(node->str, '=');
		for (alias_str = node->str; alias_str <= ptr; alias_str++)
			c_put_char(*alias_str);
		c_put_char('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * h_alias - mocks built-in alias
 * @info:  function pointer
 *	Return: always 0
 */
int h_alias(ss_info *info)
{
	int i = 0;
	char *ptr = NULL;
	list_str *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _str_chr(info->argv[i], '=');
		if (ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(nd_s_bg(info->alias, info->argv[i], '='));
	}
	return (0);
}

/**
 * alias_alter - replaces an alias
 * @info: struct
 * Return: 1 if replaced, else 0
 */
int alias_alter(ss_info *info)
{
	int i;
	list_str *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = nd_s_bg(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _str_chr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _str_dup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}

	return (1);
}
