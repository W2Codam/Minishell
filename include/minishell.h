/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:40:22 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/15 21:12:14 by pvan-dij      ########   odam.nl         */
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
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <limits.h> // TODO: Remove for MacOS
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# define EXIT_NOTFOUND 127
# define TITLE "\e[104m MongolShell \e[49m\e[94m\e[92m❱ \e[0m"

/**
 * Only global variable since its VERY useful!
 * 
 * @param stdin_fd The original INPUT stream
 * @param stdout_fd The original OUTPUT stream
 */
struct s_shell	g_shell;

//////////////////////////////////////////////////////////////////

//= Types =//

// Functor for build in commands.
typedef int32_t	(*t_func)(int32_t, char **, t_list *envp);

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
	char	*key;
	char	*value;
	bool	hidden;
	bool	unset;
}	t_var;

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
 * Important states to save about the shell that are
 * globally available.
 * 
 * @param stdin The original stdin fd.
 * @param stdout The original stdout fd.
 */
typedef struct s_shell
{
	int32_t	stdin_fd;
	int32_t	stdout_fd;
}	t_shell;

typedef struct s_qouted
{
	char	*arg;
	bool	qouted;
}	t_qoute;

//////////////////////////////////////////////////////////////////

//= Build-Ins =//

int32_t	ft_cd(int32_t argc, char **argv, t_list *envp);
int32_t	ft_echo(int32_t argc, char **argv, t_list *envp);
int32_t	ft_env(int32_t argc, char **argv, t_list *envp);
int32_t	ft_export(int32_t argc, char **argv, t_list *envp);
int32_t	ft_pwd(int32_t argc, char **argv, t_list *envp);
int32_t	ft_unset(int32_t argc, char **argv, t_list *envp);

//= Unix Utils =//

char	**ft_env_get_arr(t_list *envp);
bool	ft_env_set(t_list *envp, char *key, char *value);
t_var	*ft_env_get(t_list *envp, char *key);
char	*ft_getexec(const char *cmd, t_list *envp);
bool	ft_pipe(int32_t fds[2]);
bool	ft_access(const char *path, int32_t flags);
bool	ft_fork(pid_t *pid);
int32_t	ft_openfile(char *path, bool isoutput);

//= Shell =//

void	ft_shell(t_list *env);
void	ft_error(int32_t errovr, const char *s, char *msg);
t_list	*ft_lexer(char *input, t_list *envp);
t_list	*ft_parser(char **input);

//= Utils =//

void	exitout(char *s);
int		selectstate(char c, int state);
char	**ft_stringexpand(char *in, t_list *envp);
char	**splitting(char *in, int i, int state);

//= lolnorm =//

int		countchar(char *str, char c);
int		findnext(char *arg);
int		arr_strlen(char **arr);
void	addenvar(char **s, char **out, char *envar);
void	moveenvarpointer(char **s, char **out, char *envar);
bool	check(char *cmd);
int		ft_arrlen(char **arr);
t_file	*evaluate(t_file *in, t_file *out, char c);
int		testpipe(char c, int i);

#endif