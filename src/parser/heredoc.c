/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 19:54:32 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/21 19:56:02 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "temp/get_next_line.h"

static pid_t	g_pid;

void	lolhandle(int sig)
{
	kill(g_pid, SIGKILL);
}

void	runheredoc(t_file *temp, int32_t pipe[2], char *tstr, char *delim)
{
	while (true)
	{
		write(1, "heredoc> ", 9);
		tstr = get_next_line(STDIN_FILENO);
		if (tstr == NULL)
			exit(1);
		if (tstr[0] == '\n')
			;
		else if (ft_strncmp(tstr, delim, ft_strlen(tstr) - 1) == 0)
			break ;
		ft_putstr_fd(tstr, pipe[WRITE]);
		free(tstr);
	}
	exit(0);
}

t_file	*heredocshit(t_file *temp, char *delim)
{
	int32_t	pipe[2];
	int		status;
	char	*tstr;

	if (!ft_pipe(pipe) || !ft_fork(&g_pid))
		return (NULL);
	temp->fd = pipe[READ];
	if (g_pid == 0)
	{
		runheredoc(temp, pipe, tstr, delim);
	}	
	signal(SIGINT, lolhandle);
	waitpid(0, &status, 0);
	signal(SIGINT, ft_sig_handle);
	if (status > 0)
		return (close(pipe[WRITE]), NULL);
	close(pipe[WRITE]);
	return (temp);
}
