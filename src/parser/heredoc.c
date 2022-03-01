/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/21 19:54:32 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/01 17:59:39 by pvan-dij      ########   odam.nl         */
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

void	runheredoc(int32_t pipe[2], char *tstr, char *delim)
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
		tstr = handleenvar(tstr);
		if (!tstr)
			exit(1);
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

	if (!ft_pipe(pipe) || !ft_fork(&(g_shell->child)))
		return (NULL);
	temp->fd = pipe[READ];
	tstr = NULL;
	if (g_shell->child == 0)
	{
		runheredoc(pipe, tstr, delim);
	}	
	signal(SIGINT, lolhandle);
	waitpid(0, &status, 0);
	signal(SIGINT, ft_sig_handle);
	if (status > 0)
		return (close(pipe[WRITE]), NULL);
	close(pipe[WRITE]);
	return (temp);
}
