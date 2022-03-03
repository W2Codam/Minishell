/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:06:03 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/03/03 14:42:09 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		temp->path = ft_strdup(filename);
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

char	*checkforqoute(char *s, int state)
{
	const char	qt[2] = {'\"', '\''};
	char		*out;
	char		*save;

	if (!checkinvalid(s))
		return (s);
	out = malloc(ft_strlen(s));
	if (!out)
		return (s);
	save = out;
	while (*s)
	{
		if ((*s == '\'' || *s == '\"') && state == -1)
			state = selectstate(*s++, state);
		else if (state >= 0 && *s == qt[state])
			state = selectstate(*s++, state);
		else
			*out++ = *s++;
	}
	*out = 0;
	return (s = save, s);
}

int	parseone(char **input, t_cmd **temp, int i, int *j)
{
	while (input[i] != NULL)
	{
		if (input[i][0] == '<' || input[i][0] == '>')
		{
			if (handleredirect(evaluate(&(*temp)->in, &(*temp)->out, \
			input[i][0]), input[i + 1], (input[i][0] == '>'), input[i]))
				return (ft_putstr_fd("Redirect error\n", STDERR_FILENO), -1);
			i += 2;
			if (input[i] != NULL && input[i][0] != '<' && \
				input[i][0] != '>' && input[i][0] != '|' && !(*temp)->cmd_name)
				(*temp)->cmd_name = ft_strdup(input[i++]);
			continue ;
		}
		if (input[i][0] == '|')
			return (testpipe(input[i + 1], i));
		if (i == 0 || input[i - 1][0] == '|')
			(*temp)->cmd_name = ft_strdup(input[i]);
		else
			(*temp)->argv[(*j)++] = ft_strdup(checkforqoute(input[i], -1));
		i++;
	}
	return (i);
}

t_cmd	*constructor(t_cmd *temp, int len)
{
	temp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!temp)
		return (NULL);
	temp->argv = ft_calloc((len + 1), sizeof(char *));
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
			return (ft_lstadd_back(&out, ft_lstnew(temp)), \
									ft_cleantbl(&out), NULL);
		temp->argv[0] = NULL;
		i = parseone(input, &temp, i, &j);
		if (i < 0)
			return (ft_lstadd_back(&out, ft_lstnew(temp)), \
									ft_cleantbl(&out), NULL);
		temp->argv[j] = NULL;
		temp->argc = j;
		ft_builtincheck(&temp);
		ft_lstadd_back(&out, ft_lstnew(temp));
	}
	return (out);
}
