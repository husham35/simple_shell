#include "shell.h"
/**
 * clr_inf - clears and inits ss_info struct
 * @info: struct
 */
void clr_inf(ss_info *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_inf - initializes ss_info struct
 * @info: struct
 * @arg_vec: argument vector
 */
void set_inf(ss_info *info, char **arg_vec)
{
	int i = 0;

	info->prg_name = arg_vec[0];
	if (info->arg)
	{
		info->argv = str_to_words(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		alias_alter(info);
		change_v(info);
	}
}

/**
 * fr_info - frees ss_info struct
 * @info: struct
 * @fields: fields to free in info struct
 */
void fr_info(ss_info *info, int fields)
{
	fr_vec(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (fields)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			fr_lst(&(info->env));
		if (info->history)
			fr_lst(&(info->history));
		if (info->alias)
			fr_lst(&(info->alias));
		fr_vec(info->environ);
		info->environ = NULL;
		byte_fr((void **)info->cmd_buf);
		if (info->fd_rd > 2)
			close(info->fd_rd);
		c_put_char(ERRFLUSH);
	}
}
