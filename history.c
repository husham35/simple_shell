#include "shell.h"

/**
 * read_hist - gets the history file
 * @info: struct
 * Return: history file
 */

char *read_hist(ss_info *info)
{
	char *buf, *dir;

	dir = c_get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (c_str_len(dir) + c_str_len(HISTFILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_str_cpy(buf, dir);
	_str_cat(buf, "/");
	_str_cat(buf, HISTFILE);
	return (buf);
}

/**
 * init_hist - creates/append to history file
 * @info: struct
 * Return: 1 on success, else -1
 */
int init_hist(ss_info *info)
{
	ssize_t fd;
	char *filename = read_hist(info);
	list_str *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		w_chars(node->str, fd);
		w_char('\n', fd);
	}
	w_char(ERRFLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rd_hist - reads history from file
 * @info: struct
 * Return: hist_lines on success, else 0
 */
int rd_hist(ss_info *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = read_hist(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			patch_hist(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		patch_hist(info, buf + last, linecount++);
	free(buf);
	info->hist_lines = linecount;
	while (info->hist_lines-- >= HISTMAX)
		del_node(&(info->history), 0);
	reset_hist_num(info);
	return (info->hist_lines);
}

/**
 * patch_hist - update history file
 * @info: contains arguments for a function pointer
 * @b: buffer
 * @lcount: the history linecount, hist_lines
 * Return: Always 0
 */
int patch_hist(ss_info *info, char *b, int lcount)
{
	list_str *node = NULL;

	if (info->history)
		node = info->history;
	ins_nd_en(&node, b, lcount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * reset_hist_num - restructures history linked list after changes
 * @info: contains arguments for a function pointer
 * Return: the new history linked list
 */
int reset_hist_num(ss_info *info)
{
	list_str *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->hist_lines = i);
}
