/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:06:03 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/21 15:13:13 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "temp/get_next_line.h"

pid_t pid = -1;

void	lolhandle(int sig)
{
	kill(pid, SIGKILL);
}

t_file	*heredocshit(t_file *temp, char *delim)
{
	int32_t	pipe[2];
	int		status;
	char	*tstr;

	if (!ft_pipe(pipe))
		return (NULL);
	pid = fork();
	temp->fd = pipe[READ];
	if (pid == 0)
	{
		while (true)
		{
			write(1, "heredoc> ", 9);
			tstr = get_next_line(STDIN_FILENO);
			if (tstr == NULL)
				return (close(pipe[WRITE]), NULL);
			if (tstr[0] == '\n')
				;
			else if (ft_strncmp(tstr, delim, ft_strlen(tstr) - 1) == 0)
				break ;
			ft_putendl_fd(tstr, pipe[WRITE]);
			free(tstr);
		}
		exit(0);
	}	
	signal(SIGINT, lolhandle);
	waitpid(0, &status, 0);
	signal(SIGINT, ft_sig_handle);
	if (status > 0)
		return (close(pipe[WRITE]), NULL);
	free(tstr);
	close(pipe[WRITE]);
	return (temp);
}

bool	handleredirect(t_file *temp, char *filename, bool write, char *input)
{
	if (!filename)
		return (true);
	if (input[1] == '<')
	{
		if (!check(filename))
			return (true);
		temp = heredocshit(temp, filename);
		if (!temp)
			return (true);
	}
	else if (check(filename))
	{
		temp->path = filename;
		if (temp->fd > 2)
			close(temp->fd);
		temp->fd = -1;
		if (handleallpaths(temp, write, (input[1] == '>')) < 0)
			return (true);
	}
	else
		return (true);
	return (false);
}

int	parseone(char **input, t_cmd **temp, int i, int *j)
{
	while (input[i] != NULL)
	{
		if (input[i][0] == '<' || input[i][0] == '>')
		{
			if (handleredirect(evaluate(&(*temp)->in, &(*temp)->out, \
			input[i][0]), input[i + 1], (input[i][0] == '>'), input[i]))
				return (-1);
			i += 2;
			if (input[i] != NULL && input[i][0] != '<' && \
				input[i][0] != '>' && input[i][0] != '|')
				(*temp)->cmd_name = input[i++];
			continue ;
		}
		if (input[i][0] == '|')
			return (testpipe(input[i + 1][0], i));
		if (i == 0 || input[i - 1][0] == '|')
			(*temp)->cmd_name = input[i];
		else
			(*temp)->argv[(*j)++] = input[i];
		i++;
	}
	return (i);
}

t_cmd	*constructor(t_cmd *temp, int len)
{
	temp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!temp)
		return (NULL);
	temp->argv = malloc((len + 1) * sizeof(char *));
	if (!temp->argv)
	{
		free(temp);
		return (NULL);
	}
	temp->cmd_name = NULL;
	temp->in.fd = STDIN_FILENO;
	temp->in.path = NULL;
	temp->out.fd = STDOUT_FILENO;
	temp->out.path = NULL;
	temp->builtin = NULL;
	return (temp);
}

/**
 * Tries to insert the given input into a command table.
 * 
 * @param input The given string input.
 * @return NULL on fail or valid command structure on success
 */
t_list	*ft_parser(char **input)
{
	int		i;
	int		j;
	t_list	*out;
	t_cmd	*temp;

	i = 0;
	out = NULL;
	while (input[i] != NULL)
	{		
		j = 1;
		temp = constructor(temp, ft_arrlen(input));
		if (!temp)
			return (NULL); // failed malloc, free possible previous mallocs in out
		temp->argv[0] = NULL;
		i = parseone(input, &temp, i, &j);
		if (i < 0)
			return (NULL); // handle previous mallocs
		temp->argv[j] = NULL;
		temp->argc = j;
		ft_builtincheck(&temp);
		ft_lstadd_back(&out, ft_lstnew(temp));
	}
	return (out);
}

//TODO: norm, fucking norm
//TODO: mallocs || error return