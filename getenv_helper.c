#include "shell.h"

/**
 * c_get_env - gets the value of an environ variable
 * @info: contains arguments for a function pointer
 * @n: env var name
 * Return: pointer value
 */

char *c_get_env(ss_info *info, const char *n)
{
	char *p;
	list_str *node = info->env;

	while (node)
	{
		p = chk_prefix(node->str, n);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * chk_set_env - checks if an environment variable has been set.
 * @info: contains arguments for a function pointer
 * Return: 0 if set, else 1.
 */

int chk_set_env(ss_info *info)
{
	if (info->argc != 3)
	{
		puts_err("Incorrect number of arguements\n");
		return (1);
	}

	if (c_set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * chk_unset_env - Remove an environment variable
 * @info: contains arguments for a function pointer
 * Return: Always 0
 */
int chk_unset_env(ss_info *info)
{
	int i;

	if (info->argc == 1)
	{
		puts_err("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		c_unset_env(info, info->argv[i]);

	return (0);
}

/**
 * pop_env_lst - populates env linked list
 * @info: contains arguments for a function pointer
 * Return: Always 0
 */
int pop_env_lst(ss_info *info)
{
	list_str *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		ins_nd_en(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 * c_print_env - prints the current environment
 * @info: contains arguments for a function pointer
 * Return: Always 0
 */
int c_print_env(ss_info *info)
{
	pr_lst_str(info->env);
	return (0);
}
