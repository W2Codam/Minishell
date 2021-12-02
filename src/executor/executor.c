/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 19:39:02 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/02 14:02:20 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

/**
 * Depending on the file descriptor we re-direct our
 * file descriptors.
 * 
 * @param fds The 3 main file descriptors, in, out, err.
 * @param cmd The command table.
 */
static void	ft_redir_fds(int32_t fds[3], t_cmd *cmd)
{
	if (cmd->in.fd != STDIN_FILENO && ft_valid_file(&cmd->in))
	{
		fds[0] = ft_openfile(cmd->in.path, false);
		dup2(fds[0], STDIN_FILENO);
	}
	if (cmd->out.fd != STDOUT_FILENO && ft_valid_file(&cmd->out))
	{
		fds[1] = ft_openfile(cmd->out.path, true);
		dup2(fds[1], STDOUT_FILENO);
	}
	if (cmd->err.fd != STDERR_FILENO && ft_valid_file(&cmd->err))
	{
		fds[2] = ft_openfile(cmd->err.path, true);
		dup2(fds[2], STDERR_FILENO);
	}
}

/** 
 * The executor, takes in an array of "commands"
 * and executes them as instructed.
 */
bool	ft_run_executor(t_cmd *cmds, char **envp)
{	
	SHUTFUCK(envp);
	t_cmd	*orig;
	int32_t	fds[3];

	orig = cmds;
	while (cmds)
	{
		ft_redir_fds(fds, cmds);
		if (cmds->built_in)
		{
			/* code */
		}
		else
			execve(ft_getexec(cmds->cmd_name, envp), cmds->args, envp);
		cmds++;
	}
	close(fds[0]);
	close(fds[1]);
	close(fds[1]);
	return (true);
}
