/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:40:22 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 18:22:37 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/** 
 * __  __                   _ ___ _        _ _ 
 * |  \/  |___ _ _  __ _ ___| / __| |_  ___| | |
 * | |\/| / _ \ ' \/ _` / _ \ \__ \ ' \/ -_) | |
 * |_|  |_\___/_||_\__, \___/_|___/_||_\___|_|_|
 *                 |___/                                 
 * by W2.Wizard (lde-la-h) & TheBriar (pvan-dij)
 */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# define EXIT_NOTFOUND 127
# define TITLE "\e[103m\e[30m 0 \e[104m MongolShell \e[49m\e[94m\e[92m❱ \e[0m"
// \001\x1b[1m\002\x1b[40;31m\002hell\001\x1b[0m\002hells\001> \001\x1b[0m\002
//////////////////////////////////////////////////////////////////

//= Types =//

// Functor for build in commands.
typedef int32_t	(*t_func)(int32_t argc, char ** argv);

// Custom pipe enum.
typedef enum e_pipe
{
	WRITE = 0,
	READ = 1
}	t_pipe;

// Enum for qoutations
typedef enum s_qtype
{
	DOUBLE = 0,
	SINGLE = 1
}	t_qtype;

/**
 * A single file, similar to FILE*
 * 
 * @param fd The file descriptor for that file, -1 if not opened or existing.
 * @param path The path to the file, null if not existent.
 */
typedef struct s_file
{
	int32_t	fd;
	char	*path;
}	t_file;

/**
 * A single environment variable.
 * 
 * @param key The variable name.
 * @param value The value of the of the variable
 * @param hidden Should it be displayed with env ?
 * @param unset Allow unsetting? 
 * If true, if variable gets unset, it gets hidden instead.
 */
typedef struct s_var
{
	char			*key;
	char			*value;
	bool			hidden;
	struct s_var	*next;
}	t_var;

typedef struct s_shell
{
	t_var	*environ;
	pid_t	child;
}	t_shell;

/**
 * Only global variable since its VERY useful!
 */
extern t_shell	*g_shell;

/**
 * A single command in a linked list 
 * 
 * @param cmd_name The name of the command.
 * @param argv First arg always path to cmd, rest usual args.
 * @param argc Argument count.
 * @param in Input stream
 * @param out Output stream
 * @param builtin If function is built in, this will not be null.
 */
typedef struct s_cmd
{
	char			*cmd_name;
	char			**argv;
	int32_t			argc;
	t_file			in;
	t_file			out;
	t_func			builtin;
}	t_cmd;

/**
 * For adding builtins to cmd_table if necessary
 * 
 * @param str name of the command
 * @param builtin function pointer to the builtin
 */
typedef struct s_builtins
{
	char	*str;
	t_func	builtin;
}	t_btin;

//////////////////////////////////////////////////////////////////

//= Build-Ins =//

int32_t	ft_cd(int32_t argc, char **argv);
int32_t	ft_echo(int32_t argc, char **argv);
int32_t	ft_env(int32_t argc, char **argv);
int32_t	ft_export(int32_t argc, char **argv);
int32_t	ft_pwd(int32_t argc, char **argv);
int32_t	ft_unset(int32_t argc, char **argv);

//= Unix Utils =//

t_var	*ft_env_get(char *key);
bool	ft_env_add(char *key, char *value);
char	**ft_lst_to_arr(t_var *lst);
void	ft_starthidden(const char **starthidden);
char	*ft_getexec(const char *cmd);

bool	ft_pipe(int32_t fds[2]);
bool	ft_access(const char *path, int32_t flags);
bool	ft_fork(pid_t *pid);
int32_t	ft_openfile(char *path, bool isoutput, bool append);

//= Shell =//

void	ft_shell(void);
void	ft_error(int32_t errovr, const char *s, char *msg);
t_list	*ft_lexer(char *input);
t_list	*ft_parser(char **input);

//= Utils =//

void	exitout(char *s);
void	ft_cleanup(char **out);
void	ft_cleantbl(t_list **cmds);
int		selectstate(char c, int state);
char	**ft_stringexpand(char *in);
char	**findenvars(char *arg);
char	**splitting(char *in, int i, int state);

//= Builtin =//

void	ft_builtincheck(t_cmd **cmd);
bool	ft_isvalidkey(char *str);

//= lolnorm =//

int		countchar(char *str, char c);
int		findnext(char *arg);
int		arr_strlen(char **arr);
int		testpipe(char *c, int i);
int		ft_arrlen(char **arr);
int		handleallpaths(t_file *var, bool write, bool append);
bool	check(char *cmd);
void	addenvar(char **s, char **out, char *envar);
void	moveenvarpointer(char **s, char **out, char *envar);
t_file	*evaluate(t_file *in, t_file *out, char c);
void	ft_sig_handle(int32_t sig);
t_file	*heredocshit(t_file *temp, char *delim);

#endif