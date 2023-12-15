#include "shell.h"
/**
 * main - starting point to shell program
 * @argc: number of args passed.
 * @argv: array of args passed.
 * Return: 0 on success or 1 on failure.
 */
int main(int argc, char **argv)
{
	ss_info info[] = {INFO_INIT};
	int file_des = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(file_des)
		: "r"(file_des));

	if (argc == 2)
	{
		file_des = open(argv[1], O_RDONLY);
		if (file_des == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				puts_err(argv[0]);
				puts_err(": 0: Cannot open ");
				puts_err(argv[1]);
				put_char_err('\n');
				put_char_err(ERRFLUSH);
				exit(127);
			}

			return (EXIT_FAILURE);
		}

		info->fd_rd = file_des;
	}

	pop_env_lst(info);
	rd_hist(info);
	sh_entry(info, argv);

	return (EXIT_SUCCESS);
}
