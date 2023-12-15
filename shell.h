#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdarg.h>

#define BUFFRDSIZE 1024
#define BUFFWRSIZE 1024
#define MAXWDCOUNT 100

#define ERRFLUSH -1
#define RFLAG 0
#define ORFLAG 1
#define ANDFLAG 2
#define CHFLAG 3
#define BCLOWER 1
#define BCUNSIG 2
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTFILE ".hist_sh"
#define HISTMAX 4096
#define INFO_INIT                         \
	{                                     \
		NULL, NULL, NULL, 0, 0, 0, 0,     \
			NULL, NULL, NULL, NULL, NULL, \
			0, 0, NULL, 0, 0, 0           \
	}

extern char **environ;

/**
 * struct list_str - singly linked list
 * @num: number
 * @str: a string
 * @next: next node pointer
 */
typedef struct list_str
{
	int num;
	char *str;
	struct list_str *next;
} list_str;

/**
 * struct ss_info - contains args for a function pointer,
 * @arg: string from getline with aguments
 * @argv: array of strings from arg
 * @path: path to cutrent command
 * @argc: count of arguementss from args var
 * @lines: counts of lnes of errros
 * @error_code: error code
 * @lc_flag: line count flag
 * @prg_name: executable file name(prog name)
 * @env: local copy of environment vars
 * @environ: custom-modified copy the environ
 * @history: history node of executed commands
 * @alias: alias nodr
 * @envir_change: flag for env change
 * @status: executed command's retun status
 * @cmd_buf: address of commands buffer
 * @cmd_buf_kind: command type pointer
 * @fd_rd: file descriptor for getline
 * @hist_lines: count of hstory
 */
typedef struct ss_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	size_t lines;
	int error_code;
	int lc_flag;
	char *prg_name;
	list_str *env;
	list_str *history;
	list_str *alias;
	char **environ;
	int envir_change;
	int status;
	char **cmd_buf;
	int cmd_buf_kind;
	int fd_rd;
	int hist_lines;
} ss_info;

/**
 * struct built_in - contains built-in strings
 * @type: the built-in command flag
 * @func: pointer function
 */
typedef struct built_in
{
	char *type;
	int (*func)(ss_info *);
} builtin_cmds_table;

int sh_entry(ss_info *, char **);
int w_char(char, int);
int w_chars(char *, int);

int c_str_len(char *);
int c_str_cmp(char *, char *);
int put_char_err(char);
int c_put_char(char);
int c_is_alpha(int);
int c_al_to_in(char *);

int c_get_line(ss_info *, char **, size_t *);
int c_print_env(ss_info *);
int chk_set_env(ss_info *);
int chk_unset_env(ss_info *);
int c_unset_env(ss_info *, char *);
int c_set_env(ss_info *, char *, char *);
void _puts(char *);
char *_str_cat(char *, char *);
char *_str_cpy(char *, char *);
char *_str_dup(const char *);
char *_str_n_cpy(char *, char *, int);
char *_str_n_cat(char *, char *, int);
char *_str_chr(char *, char);
char *c_mem_set(char *, char, unsigned int);
void *c_re_alloc(void *, unsigned int, unsigned int);
char *c_get_env(ss_info *, const char *);

int err_num(char *);
int h_exit(ss_info *);
int h_cd(ss_info *);
int h_help(ss_info *);
int h_history(ss_info *);
int h_alias(ss_info *);

void puts_err(char *);

char *chk_prefix(const char *, const char *);
char *dup_chars(char *, int, int);
char *file_in_path_var(ss_info *, char *, char *);
char *alter_base(long int, int, int);
char *read_hist(ss_info *);
char **gt_envir(ss_info *);
char **str_to_words(char *, char *);
char **list_to_vector(list_str *);

void cmd_chk(ss_info *);
void init_prcs(ss_info *);
void h_sigint(int);
void clr_inf(ss_info *);
void set_inf(ss_info *, char **);
void fr_info(ss_info *, int);
void fr_vec(char **);
void pr_errs(ss_info *, char *);
void h_comments(char *);
void fr_lst(list_str **);
void chk_chn(ss_info *, char *, size_t *, size_t, size_t);
int h_in_builts(ss_info *);

bool chk_exec(ss_info *, char *);

int hsh_lp(char **);

int byte_fr(void **);
int frm_trm(ss_info *);
int pr_deci(int, int);
int pop_env_lst(ss_info *);
int init_hist(ss_info *);
int rd_hist(ss_info *);
int patch_hist(ss_info *, char *, int);
int reset_hist_num(ss_info *);
int del_node(list_str **, unsigned int);
bool chk_chained(ss_info *, char *, size_t *);
int alias_alter(ss_info *);
int change_v(ss_info *);
int str_alter(char **, char *);

list_str *ins_nd_bg(list_str **, const char *, int);
list_str *ins_nd_en(list_str **, const char *, int);
list_str *nd_s_bg(list_str *, char *, char);

size_t pr_lst_str(const list_str *);
size_t _ls_len(const list_str *);
size_t pr_lst(const list_str *);

ssize_t gt_input_inf(ss_info *);
ssize_t gt_nd_ind(list_str *, list_str *);

char **expld_str(char *, char *, size_t *);
int wds_cnt(char *, char *, unsigned int *);
void mk_zeroes(unsigned int *, size_t);
void mk_nls(char *, size_t);
bool chk_delim(char, char *);

#endif /* SHELL_H */
