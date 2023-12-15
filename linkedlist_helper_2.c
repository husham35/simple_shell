#include "shell.h"

/**
 * mk_zeroes - initialises array members with 0
 * @arr: array to be initialised.
 * @s: size of array
 * Return: void
 */

void mk_zeroes(unsigned int *arr, size_t s)
{
	size_t x;

	for (x = 0; x < s; x++)
		arr[x] = 0;
}

/**
 * mk_nls - initialises array member with `\0`
 * @arr: Array to be initialized.
 * @s: size of array
 * Return: void
 */

void mk_nls(char *arr, size_t s)
{
	size_t x;

	for (x = 0; x < s; x++)
		arr[x] = '\0';
}
