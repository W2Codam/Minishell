/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 19:54:32 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/04 18:07:18 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "temp/get_next_line.h"

static void	lolhandle(int sig)
{	
	(void)sig;
	kill(g_shell->child, SIGKILL);
}

static char	*handleenvar(char *str)
{
	char		**envars;
	char		*save;
	char		*save2;
	char		*out;

	envars = findenvars(str);
	if (!envars)
		return (str);
	save2 = str;
	out = malloc(ft_strlen(str) + arr_strlen(envars) + 1);
	if (!out)
		return (ft_cleanup(envars), NULL);
	save = out;
	while (*str)
	{
		if (*str == '$')
			addenvar(&str, &out, *envars++);
		else
			*out++ = *str++;
	}
	*out = '\n';
	++out;
	*out = 0;
	return (free(save2), ft_cleanup(envars), save);
}

int	runheredoc(int32_t pipe[2], char *tstr, char *delim)
{
	while (true)
	{
		write(1, "heredoc> ", 9);
		tstr = get_next_line(STDIN_FILENO);
		if (tstr == NULL)
			return (close(pipe[WRITE]), 1);
		if (tstr[0] == '\n')
			;
		else if (ft_strncmp(tstr, delim, ft_strlen(tstr) - 1) == 0)
			break ;
		tstr = handleenvar(tstr);
		if (!tstr)
			return (close(pipe[WRITE]), 1);
		ft_putstr_fd(tstr, pipe[WRITE]);
		free(tstr);
	}
	return (close(pipe[WRITE]), 0);
}

t_file	*heredocshit(t_file *temp, char *delim)
{
	int32_t	pipe[2];
	int		out;
	int		status;
	char	*tstr;

	if (!ft_pipe(pipe))
		return (NULL);
	temp->fd = pipe[READ];
	tstr = NULL;
	if (!ft_fork(&(g_shell->child)))
		return (NULL);
	if (g_shell->child == 0)
	{
		close (pipe[READ]);
		out = runheredoc(pipe, tstr, delim);
		exit(out);
	}	
	signal(SIGINT, lolhandle);
	waitpid(0, &status, 0);
	signal(SIGINT, ft_sig_handle);
	if (status > 0)
		set_exit_failure();
	close(pipe[WRITE]);
	return (temp);
}
