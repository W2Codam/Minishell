/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 09:25:28 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/01 15:00:17 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

/**
 * Gets the environment variable string depending on
 * which one is requested. (basically getvar)
 * 
 * @param var The variable.
 * @param envp The environment variable ptr.
 * @return The variable including the name.
 */
char	*ft_getvar(const char *var, char **envp)
{
	size_t	var_len;
	char	*out;

	out = NULL;
	var_len = ft_strlen(var);
	while (*envp)
	{
		if (ft_strnstr(*envp, var, var_len))
			break ;
		envp++;
	}
	return ((*envp) + var_len + 1);
}

/**
 * Get the absolute executable path of a command.
 * 
 * @param cmd The command like 'ls' or 'grep'.
 * @param envp The environment variable pointer.
 * @return The absolute path to the cmd executable.
 */
char	*ft_getexec(const char *cmd, char **envp)
{
	char	*path;
	char	*temp;
	char	**paths;
	int32_t	path_index;

	path_index = -1;
	paths = ft_split(ft_getvar("PATH", envp), ':');
	while (paths[++path_index])
	{
		temp = ft_strjoin(paths[path_index], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (ft_access(path, F_OK | X_OK))
			break ;
		free(path);
		path = NULL;
	}
	path_index = -1;
	while (paths[++path_index])
		free(paths[path_index]);
	free(paths);
	return (path);
}

/** 
 * Simplified wrapper for access to return proper boolean.
 * @param path The path to the file.
 * @param flags The flags to use for checking.
 * @returns Depending on the flag wether the condition is met or not.
 */
bool	ft_access(const char *path, int32_t flags)
{
	if (access(path, flags) != -1)
		return (true);
	return (false);
}

/** 
 * Creates a unidirectional pipe.
 * @param fds Int arr of size 2.
 * @param fd0 WRITE
 * @param fd1 READ
 * @note On error check errno! Also pipes are more logically reveresed,
 * 0 was reading and 1 was writing.
 */
bool	ft_pipe(int32_t fds[2])
{
	int32_t	temp;

	if (pipe(fds) == -1)
		return (false);
	temp = fds[0];
	fds[0] = fds[1];
	fds[1] = temp;
	return (true);
}

/** 
 * Creates a new process by duplicating the calling process.
 * @param pid The new process id.
 * @returns Wether the execution was sucessfull.
 * @note Use errorn!
 */
int32_t	ft_fork(pid_t *pid)
{
	int32_t	output;

	output = fork();
	if (output == -1)
		return (false);
	*pid = output;
	return (true);
}
