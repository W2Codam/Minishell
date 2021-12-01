/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mongolshell.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 13:55:59 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/01 17:18:34 by lde-la-h      ########   odam.nl         */
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

#ifndef MONGOLSHELL_H
# define MONGOLSHELL_H
# include "libft.h"
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# define SHUTFUCK(var) (void)var
# define TITLE "\e[104m MongolShell \e[49m\e[94m\n\e[92m❱ \e[0m"
/**
 * Refactored piping for ft_pipe.
 * 
 * I (W2) personally disagree with the idea that 1 is writing and 0 is reading.
 * For me it seems more natural that 0 (as input) is writing and 1 (as output)
 * is reading. Just as we first write stuff then read it, not the other way
 * around.
 */
typedef enum e_pipe
{
	WRITE = 0,
	READ = 1
}	t_pipe;

/**
 * A file is someform out 'file' that can be read from or
 * written to.
 * @param fd	The file descriptor.
 * @param path	The path to the file, null if stdin, stdout or stderr.
 */
typedef struct s_file
{
	int32_t	fd;
	char	*path;
}	t_file;

/**
 * An entry to the command table, an entry consists of the executable
 * name, its arguments and where its IO is directed.
 * @param cmd_name	The command name.
 * @param args		The arguments being passed to the command.
 * @param 
 */
typedef struct s_cmd
{
	char	*cmd_name;
	char	*args;
	t_file	in;
	t_file	out;
	t_file	err;
}	t_cmd;

//= Unix Utils =//

char	*ft_getvar(const char *var, char **envp);
char	*ft_getexec(const char *cmd, char **envp);
bool	ft_access(const char *path, int32_t flags);
bool	ft_pipe(int32_t fds[2]);
int32_t	ft_fork(pid_t *pid);

#endif