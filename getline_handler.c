#include "shell.h"

/**
 * input_buf - buffers chk_chained commands
 * @info: struct
 * @b: addr of buffer
 * @len: addr of len variable
 *
 * Return: bytes read
 */
ssize_t input_buf(ss_info *info, char **b, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*b);
		*b = NULL;
		signal(SIGINT, h_sigint);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = c_get_line(info, b, &len_p);
#endif
		if (r > 0)
		{
			if ((*b)[r - 1] == '\n')
			{
				(*b)[r - 1] = '\0'; /* discard trailing newline */
				r--;
			}
			info->lc_flag = 1;
			h_comments(*b);
			patch_hist(info, *b, info->hist_lines++);
			/* if (_str_chr(*b, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = b;
			}
		}
	}
	return (r);
}

/**
 * gt_input_inf - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t gt_input_inf(ss_info *info)
{
	static char *b; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	c_put_char(ERRFLUSH);
	r = input_buf(info, &b, &len);
	if (r == -1) /* checks if EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = b + i;

		chk_chn(info, b, &j, i, len);
		while (j < len)
		{
			if (chk_chained(info, b, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_kind = RFLAG;
		}
		*buf_p = p;
		return (c_str_len(p));
	}
	*buf_p = b;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @info: struct
 * @b: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(ss_info *info, char *b, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->fd_rd, b, BUFFRDSIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * c_get_line - gets next line of input from STDIN
 * @info: struct
 * @ptr: addr to buffer, preallocated or NULL
 * @ln: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int c_get_line(ss_info *info, char **ptr, size_t *ln)
{
	static char buf[BUFFRDSIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && ln)
		s = *ln;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _str_chr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = c_re_alloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* in case of malloc failure */
		return (p ? free(p), -1 : -1);
	if (s)
		_str_n_cat(new_p, buf + i, k - i);
	else
		_str_n_cpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (ln)
		*ln = s;
	*ptr = p;
	return (s);
}

/**
 * h_sigint - prevents ctrl+C
 * @sig_num: signal number
 * Return: void
 */
void h_sigint(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	c_put_char(ERRFLUSH);
}
