#include "shell.h"
/**
 * _ls_len - gets length of linked list
 * @hd: first node
 * Return: Size of list.
 */
size_t _ls_len(const list_str *hd)
{
	size_t i = 0;

	while (hd)
	{
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
 * list_to_vector - returns an array of strings
 * @h: first node
 * Return: array of strings.
 */

char **list_to_vector(list_str *h)
{
	list_str *node = h;
	size_t i = _ls_len(h), j;
	char **strs;
	char *str;

	if (!h || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));

	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(c_str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = _str_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * pr_lst - prints elements of linked list
 * @hd: first node
 * Return: size of list
 */

size_t pr_lst(const list_str *hd)
{
	size_t i = 0;

	while (hd)
	{
		_puts(alter_base(hd->num, 10, 0));
		c_put_char(':');
		c_put_char(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
 * nd_s_bg - returns node that has a prefix
 * @h: head node
 * @ptr_pref: prefix to check
 * @ch: character after prefix to check
 * Return: matching node else null
 */

list_str *nd_s_bg(list_str *h, char *ptr_pref, char ch)
{
	char *ptr = NULL;

	while (h)
	{
		ptr = chk_prefix(h->str, ptr_pref);
		if (ptr && ((ch == -1) || (*ptr == ch)))
			return (h);
		h = h->next;
	}
	return (NULL);
}

/**
 * gt_nd_ind - finds a node's index
 * @h: head
 * @n: node
 * Return: index of node else -1
 */

ssize_t gt_nd_ind(list_str *h, list_str *n)
{
	size_t i = 0;

	while (h)
	{
		if (h == n)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
