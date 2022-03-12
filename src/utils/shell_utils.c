/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 17:23:38 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/02 17:36:38 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * execute builtins that can't be executed in child processes
 * 
 * @param cmds 
 */
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

void	ft_corrupt_the_child(int32_t shitpipe[2])
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
