#include "shell.h"

/**
 * chk_exec - verifies if a file is an executable command
 * @info: info struct
 * @path: file path
 *
 * Return: 1 if true, 0 otherwise
 */
bool chk_exec(ss_info *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (true);
	}
	return (false);
}

/**
 * dup_chars - duplicates characters
 * @path_str: PATH
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_chars(char *path_str, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			buf[k++] = path_str[i];
	buf[k] = 0;
	return (buf);
}

/**
 * file_in_path_var - finds command in the PATH var
 * @info: struct
 * @path_str: PATH string
 * @command: the command to find
 * Return: full path of command if found or NULL
 */
char *file_in_path_var(ss_info *info, char *path_str, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((c_str_len(command) > 2) && chk_prefix(command, "./"))
	{
		if (chk_exec(info, command))
			return (command);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_chars(path_str, curr_pos, i);
			if (!*path)
				_str_cat(path, command);
			else
			{
				_str_cat(path, "/");
				_str_cat(path, command);
			}
			if (chk_exec(info, path))
				return (path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
