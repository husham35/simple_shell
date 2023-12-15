#include "shell.h"

/**
 * h_exit - exits the shell
 * @info: contains arguments for a function pointer
 * Return: exits with a given exit status
 */

int h_exit(ss_info *info)
{
	int exitcheck;

	if (info->argv[1]) /* if there is an exit arguement */
	{
		exitcheck = err_num(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			pr_errs(info, "Illegal number: ");
			puts_err(info->argv[1]);
			put_char_err('\n');
			return (1);
		}
		info->error_code = err_num(info->argv[1]);
		return (-2);
	}
	info->error_code = -1;
	return (-2);
}
/**
 * h_cd - mocks the original cd command
 * @info: contains arguments for a function pointer
 * Return: 0
 */

int h_cd(ss_info *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure error msg here<<\n");
	if (!info->argv[1])
	{
		dir = c_get_env(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = c_get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (c_str_cmp(info->argv[1], "-") == 0)
	{
		if (!c_get_env(info, "OLDPWD="))
		{
			_puts(s);
			c_put_char('\n');
			return (1);
		}
		_puts(c_get_env(info, "OLDPWD=")), c_put_char('\n');
		chdir_ret =
			chdir((dir = c_get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		pr_errs(info, "can't cd to ");
		puts_err(info->argv[1]), put_char_err('\n');
	}
	else
	{
		c_set_env(info, "OLDPWD", c_get_env(info, "PWD="));
		c_set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * h_help - mocks the help command
 * @info: contains arguments for a function pointer
 * Return: 0
 */

int h_help(ss_info *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);

	return (0);
}

/**
 * h_history - mocks the history command
 * @info: contains arguments for a function pointer
 *	Return: Always 0
 */

int h_history(ss_info *info)
{
	pr_lst(info->history);

	return (0);
}
