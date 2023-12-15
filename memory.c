#include "shell.h"
/**
 * c_mem_set - fills memory with a constant byte
 * @ptr: pointer to the memory area
 * @byte: bytes to fill memory area with
 * @num: the amount of bytes to be filled
 * Return: pointer to the memory area
 */
char *c_mem_set(char *ptr, char byte, unsigned int num)
{
	unsigned int i;

	for (i = 0; i < num; i++)
		ptr[i] = byte;
	return (ptr);
}

/**
 * fr_vec - frees memory to a vector
 * @v: vector to be freed.
 */

void fr_vec(char **v)
{
	char **ptr = v;

	if (!v)
		return;
	while (*v)
		free(*v++);

	free(ptr);
}

/**
 * c_re_alloc - reallocs block of memory
 * @ptr: addr to previous memory alloced block
 * @ob_size: previous block byte size
 * @nb_size: new block byte size
 * Return: addr of old block.
 */
void *c_re_alloc(void *ptr, unsigned int ob_size, unsigned int nb_size)
{
	char *p;

	if (!ptr)
		return (malloc(nb_size));
	if (!nb_size)
		return (free(ptr), NULL);
	if (nb_size == ob_size)
		return (ptr);
	p = malloc(nb_size);
	if (!p)
		return (NULL);
	ob_size = ob_size < nb_size ? ob_size : nb_size;
	while (ob_size--)
		p[ob_size] = ((char *)ptr)[ob_size];
	free(ptr);
	return (p);
}

/**
 * byte_fr - frees/nullifies a pointer and it address
 * @p: addr of the pointer to free
 * Return: 1 if successful, else 0.
 */
int byte_fr(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
