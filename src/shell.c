/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 00:08:09 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 17:59:31 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec(t_cmd *cmdval)
{
	if (cmdval->in.fd != STDIN_FILENO)
	{
		dup2(cmdval->in.fd, STDIN_FILENO);
		close(cmdval->in.fd);
	}
	if (cmdval->out.fd != STDOUT_FILENO)
	{
		dup2(cmdval->out.fd, STDOUT_FILENO);
		close(cmdval->out.fd);
	}
	cmdval->argv[0] = (char *)ft_getexec(cmdval->cmd_name);
	if (cmdval->builtin != NULL)
		exit(cmdval->builtin(cmdval->argc, cmdval->argv));
	if ((cmdval->cmd_name[0] == '.' && cmdval->cmd_name[1] == '/') || \
		(cmdval->cmd_name[0] == '.' && cmdval->cmd_name[1] == '.' && \
		cmdval->cmd_name[2] == '/') || cmdval->cmd_name[0] == '/')
		cmdval->argv[0] = cmdval->cmd_name;
	else
		cmdval->argv[0] = (char *)ft_getexec(cmdval->cmd_name);
	execve(cmdval->argv[0], cmdval->argv, ft_lst_to_arr(g_shell->environ));
	ft_putendl_fd("TRY HARDER MONGOOL COMMAND NOT FOUND!", STDERR_FILENO);
	exit (EXIT_NOTFOUND);
}

static void	ft_pipe_command(t_list *cmd, int32_t pipe[2]);

/* With the standard output plumbing sorted, execute Nth command */
void	ft_nth_command(t_list *cmd)
{
	int32_t	pipe[2];
	t_cmd	*cmdval;

	cmdval = cmd->content;
	if (cmd->prev)
	{
		if (!ft_pipe(pipe))
		{
			ft_putendl_fd("THE BLOODY PIPE!", STDERR_FILENO);
			exit (EXIT_FAILURE);
		}
		if (!ft_fork(&g_shell->child))
		{
			ft_putendl_fd("THE FUCKING FORK!", STDERR_FILENO);
			exit (EXIT_FAILURE);
		}
		if (g_shell->child == 0)
			ft_pipe_command(cmd->prev, pipe);
		dup2(pipe[READ], STDIN_FILENO);
		close(pipe[WRITE]);
		close(pipe[READ]);
	}
	ft_exec(cmdval);
}

static void	ft_pipe_command(t_list *cmd, int32_t pipe[2])
{
	t_cmd	*cmdval;

	cmdval = cmd->content;
	dup2(pipe[WRITE], STDOUT_FILENO);
	close(pipe[READ]);
	close(pipe[WRITE]);
	ft_nth_command(cmd);
}

void	ft_helpshell(int32_t shitpipe[2], t_list *cmds)
{
	ft_pipe(shitpipe);
	ft_exec_tbl(cmds, shitpipe);
	ft_corrupt_the_child(shitpipe);
	ft_cleantbl(&cmds);
}

/**
 * The behaviour loop for the shell itself.
 */
void	ft_shell(void)
{
	t_list	*cmds;
	int32_t	shitpipe[2];
	char	*line;

	while (true)
	{
		g_shell->child = -1;
		line = readline(TITLE);
		if (!line)
			ft_exit(0, NULL);
		if (*line)
		{	
			add_history(line);
			cmds = ft_lexer(line);
			if (!cmds)
			{
				free(line);
				continue ;
			}
			ft_helpshell(shitpipe, cmds);
		}
		free(line);
	}
}
