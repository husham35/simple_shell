#include "shell.h"
/**
 * err_num - converts a string to an integer
 * @str: string to converted
 * Return: 0 if no numbers in string, converted integer else -1
 */
int err_num(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
 * pr_errs - prints error message
 * @info: contains arguments for a function pointer
 * @err_str: string containing specified error type
 * Return: 0 if no numbers in string, converted integer else -1
 */
void pr_errs(ss_info *info, char *err_str)
{
	puts_err(info->prg_name);
	puts_err(": ");
	pr_deci(info->lines, STDERR_FILENO);
	puts_err(": ");
	puts_err(info->argv[0]);
	puts_err(": ");
	puts_err(err_str);
}

/**
 * pr_deci - function prints a decimal number
 * @in: input
 * @file_des: the filedescriptor to write to
 * Return: number of characters printed
 */
int pr_deci(int in, int file_des)
{
	int (*_c_put_char)(char) = c_put_char;
	int i, count = 0;
	unsigned int _abs_, current;

	if (file_des == STDERR_FILENO)
		_c_put_char = put_char_err;
	if (in < 0)
	{
		_abs_ = -in;
		_c_put_char('-');
		count++;
	}
	else
		_abs_ = in;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{

		if (_abs_ / i)
		{
			_c_put_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	_c_put_char('0' + current);
	count++;
	return (count);
}
/**
 * alter_base - a clone of itoa
 * @number: number
 * @b: base
 * @f: argument flags
 * Return: string
 */
char *alter_base(long int number, int b, int f)
{
	char sign = 0;
	char *ptr;
	unsigned long n = number;

	static char *array;
	static char buffer[50];

	if (!(f & BCUNSIG) && number < 0)
	{
		n = -number;
		sign = '-';
	}
	array = f & BCLOWER ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[n % b];
		n /= b;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * h_comments - function replaces first instance of '#' with '\0'
 * @b: address of the string to modify
 *
 * Return: 0;
 */

void h_comments(char *b)
{
	int i;

	for (i = 0; b[i] != '\0'; i++)
		if (b[i] == '#' && (!i || b[i - 1] == ' '))
		{
			b[i] = '\0';
			break;
		}
}
