/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:06:03 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/15 21:11:58 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handleallpaths(t_file *var, bool write)
{
	var->fd = ft_openfile(var->path, write);
	if (var->fd == -1)
	{
		return (-1); // something went wrong during open
	}
	return (0);
}

bool	handleredirect(t_file *temp, char *filename, bool write)
{
	if (!filename)
		return (true);
	if (check(filename))
	{
		temp->path = filename;
		temp->fd = -1;
		if (handleallpaths(temp, write) < 0)
			return (true);
	}
	else
		return (true);
	return (false);
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
	temp->out.fd = STDOUT_FILENO;
	return (temp);
}

int	parseone(char **input, t_cmd **temp, int i, int *j)
{
	while (input[i] != NULL)
	{
		if (input[i][0] == '<' || input[i][0] == '>')
		{
			if (handleredirect(evaluate(&(*temp)->in, &(*temp)->out, \
			input[i][0]), input[i + 1], (input[i][0] == '>')))
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
		ft_lstadd_back(&out, ft_lstnew(temp));
	}
	return (out);
}

//TODO: norm, fucking norm
//TODO: mallocs || error return