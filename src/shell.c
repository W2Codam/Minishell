/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 00:08:09 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 17:16:52 by lde-la-h      ########   odam.nl         */
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
static void	ft_nth_command(t_list *cmd)
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

static void	ft_corrupt_the_child(int32_t shitpipe[2])
{
	pid_t	child;
	t_var	*temp;
	int		status;

	close(shitpipe[WRITE]);
	child = waitpid(0, &status, 0);
	read(shitpipe[READ], NULL, 10);
	if (child != -1)
	{
		temp = ft_env_get("?");
		free(temp->value);
		temp->value = ft_itoa(WEXITSTATUS(status));
		if (!temp->value)
			exit(EXIT_FAILURE);
	}
}

t_list	*filteroutbuiltin(t_list *cmds)
{
	t_list	*cmdcpy;
	t_cmd	*temp;

	cmdcpy = cmds;
	while (cmdcpy)
	{
		temp = cmdcpy->content;
		if (temp->builtin && (temp->builtin == ft_unset || \
			temp->builtin == ft_export || temp->builtin == ft_cd) \
				&& !cmdcpy->prev && !cmdcpy->next)
		{
			g_shell->child = 1;
			temp->builtin(temp->argc, temp->argv);
			return (NULL);
		}
		cmdcpy = cmdcpy->next;
	}
	return (cmds);
}

/**
 * We need to forward our pipe output to the next process so it can 
 * listen/read from it as stdin then we continue down this chain. 
 * Until the last process.
 * 
 * So we want to run basically each command and just make 
 * them forward their pipe's output to the next command.
 * 
 * TODO: NOORMMEEEEEEEEEREEQWDQWDQWDEFSDGSDFGSDGSRTGH
 * 
 * @param cmds 
 * @param env 
 */
void	ft_exec_tbl(t_list *cmds, int32_t shitpipe[2])
{
	t_list	*cmds_cpy;

	cmds_cpy = ft_lstlast(filteroutbuiltin(cmds));
	if (!cmds_cpy)
		return ((void)close(shitpipe[READ]));
	if (!ft_fork(&g_shell->child))
	{
		ft_putendl_fd("shell: Fork failure!", STDERR_FILENO);
		return ;
	}
	if (g_shell->child != 0)
		return ;
	close(shitpipe[READ]);
	ft_nth_command(cmds_cpy);
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
		if ((!line) || ft_strncmp(line, "exit", 4) == 0)
			return (exitout(line));
		if (*line)
		{	
			add_history(line);
			cmds = ft_lexer(line);
			if (!cmds)
			{
				free(line);
				continue ;
			}
			ft_pipe(shitpipe);
			ft_exec_tbl(cmds, shitpipe);
			ft_corrupt_the_child(shitpipe);
			ft_cleantbl(&cmds);
		}
		free(line);
	}
}
