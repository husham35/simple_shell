#include "shell.h"

/**
 * ins_nd_bg - inserts a node to the beginning of the list
 * @h: addr to head node
 * @d: data part of node
 * @ind: node index used by history
 * Return: size of list
 */
list_str *ins_nd_bg(list_str **h, const char *d, int ind)
{
	list_str *new_h;

	if (!h)
		return (NULL);
	new_h = malloc(sizeof(list_str));
	if (!new_h)
		return (NULL);
	c_mem_set((void *)new_h, 0, sizeof(list_str));
	new_h->num = ind;
	if (d)
	{
		new_h->str = _str_dup(d);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *h;
	*h = new_h;
	return (new_h);
}

/**
 * ins_nd_en - inserts a node to the end of the list
 * @h: addr to head node
 * @d: data part of node
 * @ind: node index used by history
 * Return: size of list
 */
list_str *ins_nd_en(list_str **h, const char *d, int ind)
{
	list_str *new_n, *node;

	if (!h)
		return (NULL);

	node = *h;
	new_n = malloc(sizeof(list_str));
	if (!new_n)
		return (NULL);
	c_mem_set((void *)new_n, 0, sizeof(list_str));
	new_n->num = ind;
	if (d)
	{
		new_n->str = _str_dup(d);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_n;
	}
	else
		*h = new_n;
	return (new_n);
}

/**
 * pr_lst_str - prints data field of list_str linked list
 * @hd: first node
 * Return: size of list
 */
size_t pr_lst_str(const list_str *hd)
{
	size_t i = 0;

	while (hd)
	{
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
 * del_node - deletes node at given index
 * @h: addr to first node
 * @ind: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int del_node(list_str **h, unsigned int ind)
{
	list_str *node, *prev_n;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!ind)
	{
		node = *h;
		*h = (*h)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == ind)
		{
			prev_n->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_n = node;
		node = node->next;
	}
	return (0);
}

/**
 * fr_lst - frees all nodes of linkedlist
 * @h_p: addr to head node
 * Return: void
 */
void fr_lst(list_str **h_p)
{
	list_str *node, *next_n, *h;

	if (!h_p || !*h_p)
		return;
	h = *h_p;
	node = h;
	while (node)
	{
		next_n = node->next;
		free(node->str);
		free(node);
		node = next_n;
	}
	*h_p = NULL;
}
