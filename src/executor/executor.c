/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 19:39:02 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/02 16:34:57 by lde-la-h      ########   odam.nl         */
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
 * Executes the given shell command.
 * Command can be given as an absolute path like "/bin/ls" or
 * by just typing "ls". If command does not exists
 * 
 * @param cmd The whole command with args.
 * @param envp Enviroment pointer.
 */
static void	ft_exec(t_cmd *cmds, char **envp)
{
	if (!cmds->built_in)
		execve(ft_getexec(cmds->cmd_name, envp), cmds->args, envp);
	ft_assert("Command does not exist");
}

/**
 * Executes a child process with the given cmd.
 * Creating a pipe to the parent process.
 * 
 * @param cmds A single command that will store its output in the pipe.
 * @param envp The environment pointer.
 */
static void	ft_exec_child(t_cmd *cmds, char **envp)
{
	pid_t	pid;
	int32_t	fds[2];

	if (!ft_pipe(fds) || !ft_fork(&pid))
	{
		ft_assert("Pipe/Fork failure!");
		return (false);
	}
	if (pid == 0)
	{
		close(fds[READ]);
		dup2(fds[WRITE], STDOUT_FILENO);
		ft_exec(cmds, envp);
	}
	else
	{
		close(fds[WRITE]);
		dup2(fds[READ], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

/** 
 * The executor, takes in an array of "commands"
 * and executes them as instructed.
 * TODO: This might not be setup just right.
 */
bool	ft_run_executor(t_cmd *cmds, char **envp)
{	
	int32_t		fds[3];
	const t_cmd	*cmd_orig = cmds;

	while (cmds)
	{
		ft_redir_fds(fds, cmds);
		if (cmds->next) // Theres a pipe, execute child!
			ft_exec_child(cmds, envp);
		else // Just a single command. with a probable re-director.
			ft_exec(cmds, envp);
		cmds++;
	}
	free((void *)cmd_orig);
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
	return (true);
}