/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:08:27 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 19:37:30 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * TODO: Leak proof this.
 * Get the absolute executable path of a command.
 * 
 * @param cmd The command like 'ls' or 'grep'.
 * @param envp The environment variable pointer.
 * @return The absolute path to the cmd executable or NULL on failure.
 */
char	*ft_getexec(const char *cmd)
{
	int32_t		i;
	size_t		len;
	char		**paths;
	char		path[PATH_MAX];
	const t_var	*enval = ft_env_get("PATH");

	i = -1;
	if (enval->hidden)
		return (NULL);
	paths = ft_split(enval->value, ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		len = ft_strlen(paths[i]);
		memset(path, '\0', sizeof(path));
		memmove(path, paths[i], len);
		path[len++] = '/';
		memmove(&path[len], cmd, ft_strlen(cmd));
		if (ft_access(path, F_OK | X_OK))
			return (ft_strdup(path));
		free(paths[i]);
	}
	free(paths);
	return (NULL);
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
bool	ft_fork(pid_t *pid)
{
	int32_t	output;

	output = fork();
	if (output == -1)
		return (false);
	*pid = output;
	return (true);
}
