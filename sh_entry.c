#include "shell.h"

/**
 * sh_entry - entry point for program
 * @info: ss_info struct with shell information
 * @av: array of arguments to the shell
 * Return: status of executed builtin command
 */
int sh_entry(ss_info *info, char **av)
{
	ssize_t rd_res = 0;
	int b_val_ret = 0;

	while (rd_res != -1 && b_val_ret != -2)
	{
		clr_inf(info);

		if (frm_trm(info))
			_puts("$ ");

		put_char_err(ERRFLUSH);
		rd_res = gt_input_inf(info);
		if (rd_res != -1)
		{
			set_inf(info, av);
			b_val_ret = h_in_builts(info);

			if (b_val_ret == -1)
				cmd_chk(info);
		}
		else if (frm_trm(info))
			c_put_char('\n');

		fr_info(info, 0);
	}

	init_hist(info);

	fr_info(info, 1); /* free memory and exit programme*/
	if (!frm_trm(info) && info->status)
		exit(info->status);

	if (b_val_ret == -2) /* exit with error */
	{
		if (info->error_code == -1)
			exit(info->status);
		exit(info->error_code);
	}

	return (b_val_ret); /* last executed in-built command status */
}

/**
 * cmd_chk - searches for a command in PATH or the current directory
 * @info: a pointer to info struct
 * Return: void
 */
void cmd_chk(ss_info *info)
{
	char *path = NULL;
	int i, wd_count;

	info->path = info->argv[0];
	if (info->lc_flag == 1)
	{
		info->lines++;
		info->lc_flag = 0;
	}

	for (i = 0, wd_count = 0; info->arg[i]; i++)
		if (!chk_delim(info->arg[i], " \t\n"))
			wd_count++;

	if (!wd_count) /* exit if there are no word count */
		return;

	path = file_in_path_var(info, c_get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		init_prcs(info);
	}
	else
	{
		/* check if the command is in the current directory */
		if ((frm_trm(info) || c_get_env(info, "PATH=") || info->argv[0][0] == '/') && chk_exec(info, info->argv[0]))
			init_prcs(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			pr_errs(info, "not found\n");
		}
	}
}

/**
 * init_prcs - forks a new process to run the command
 * @info: pointer to the parameter & return info struct
 * Return: void
 */
void init_prcs(ss_info *info)
{
	pid_t child_pid;

	child_pid = fork(); /* fork a new process */
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0) /* child process: execute the command */
	{
		if (execve(info->path, info->argv, gt_envir(info)) == -1)
		{
			fr_info(info, 1); /* Handle execve errors */
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else /* wait for child process to finish */
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			/* child's exit status */
			info->status = WEXITSTATUS(info->status);

			/* permission denied err */
			if (info->status == 126)
				pr_errs(info, "Permission denied\n");
		}
	}
}

/**
 * h_in_builts - finds a in-built command
 * @info: the parameter & return info struct
 * Return: -1 if in-built not found,
 * 0 if in-built executed successfully,
 * 1 if in-built found but not successful,
 * 2 if in-built signals exit()
 */
int h_in_builts(ss_info *info)
{
	int i, b_val_ret = -1;

	builtin_cmds_table b_cmds[] = {
		{"cd", h_cd},
		{"env", c_print_env},
		{"exit", h_exit},
		{"help", h_help},
		{"alias", h_alias},
		{"setenv", chk_set_env},
		{"history", h_history},
		{"unsetenv", chk_unset_env},
		{NULL, NULL}};

	for (i = 0; b_cmds[i].type; i++)
		if (c_str_cmp(info->argv[0], b_cmds[i].type) == 0)
		{
			info->lines++;
			b_val_ret = b_cmds[i].func(info);
			break;
		}
	return (b_val_ret);
}
