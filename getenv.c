#include "shell.h"

/**
 * gt_envir - Returns array of the environment variables
 * @info: contains arguments for a function pointer
 * Return: environment variables as an array of strings.
 */

char **gt_envir(ss_info *info)
{
	if (!info->environ || info->envir_change)
	{
		info->environ = list_to_vector(info->env);
		info->envir_change = 0;
	}
	return (info->environ);
}

/**
 * c_set_env - adds/patches an environment variable.
 * @info: contains arguments for a function pointer
 * @var: environment variable to add/update.
 * @val: value of the environment variable to add/update.
 * Return: 0 if success, else 1.
 */

int c_set_env(ss_info *info, char *var, char *val)
{
	char *buf = NULL;
	list_str *node;
	char *p;

	if (!var || !val)
		return (1);
	buf = malloc(c_str_len(var) + c_str_len(val) + 2);
	if (!buf)
		return (1);
	_str_cpy(buf, var);
	_str_cat(buf, "=");
	_str_cat(buf, val);

	node = info->env;
	while (node)
	{
		p = chk_prefix(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->envir_change = 1;
			return (0);
		}
		node = node->next;
	}

	ins_nd_en(&(info->env), buf, 0);
	free(buf);
	info->envir_change = 1;
	return (0);
}

/**
 * c_unset_env - unsets an environment variable.
 * @info: contains arguments for a function pointer
 * @var: The name of the environment variable to remove.
 * Return: 1 if successful, else 0.
 */
int c_unset_env(ss_info *info, char *var)
{
	list_str *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = chk_prefix(node->str, var);
		if (p && *p == '=')
		{
			info->envir_change = del_node(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}

	return (info->envir_change);
}
