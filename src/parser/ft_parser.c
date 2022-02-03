/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:06:03 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/03 00:22:34 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

bool	check(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (len == 1)
	{
		if (cmd[0] == '>' || cmd[0] == '<' || cmd[0] == '|')
			return (false);
	}
	else if (len == 2)
	{
		if (ft_strncmp(cmd, "<<", 2) || ft_strncmp(cmd, ">>", 2))
			return (false);
	}
	return (true);
}

bool	handleredirect(t_cmd **temp, char *direct, char *filename)
{
	if (direct[0] == '<')
	{
		if (check(filename))
		{
			(*temp)->in.path = filename;
			(*temp)->in.fd = -1;
		}
		else
			return (false);
	}
	else if (direct[0] == '>')
	{
		if (check(filename))
		{
			(*temp)->out.path = filename;
			(*temp)->out.fd = -1;
		}
		else
			return (false);
	}
	return (true);
}

int	handlepaths(t_cmd **temp)
{
	if ((*temp)->in.fd == STDIN_FILENO)
		(*temp)->in.path = NULL;
	else
	{
		if (!access((*temp)->in.path, F_OK))
			if (access((*temp)->in.path, R_OK))
				return (1); // failed to acces error
	}
	if ((*temp)->out.fd == STDOUT_FILENO)
		((*temp)->out.path = NULL);
	else
	{
		if (!access((*temp)->out.path, F_OK))
			if (access((*temp)->out.path, W_OK))
				return (1); // failed to acces error
	}
	return (0);
}

/**
 * Tries to insert the given input into a command table.
 * 
 * @param input The given string input.
 * @return NULL on fail or valid command structure
 */
t_list *ft_parser(char **input, t_list *envp)
{
	int		i;
	int		j;
	t_list	*out;
	t_cmd	*temp;

	i = 0;
	out = NULL;
	(void) envp;
	while (input[i] != NULL)
	{		
		j = 1;
		temp = (t_cmd *)malloc(sizeof(t_cmd));
		if (!temp)
			return (NULL); // cleanup of possible previous mallocs
		temp->argv = malloc(ft_arrlen(input) * sizeof(char *));
		temp->in.fd = STDIN_FILENO;
		temp->out.fd = STDOUT_FILENO;
		if (input[i][0] == '<' || input[i][0] == '>')
		{
			if (!handleredirect(&temp, input[i], input[i + 1]))
				return (NULL);
			i += 2;
		}
		if (input[i][0] == '|')
		{
			temp->cmd_name = NULL;
			temp->argv[0] = NULL;
			handlepaths(&temp);
			ft_lstadd_back(&out, ft_lstnew(temp));
			i++;
			continue ;
		}
		else
			temp->cmd_name = input[i];
		temp->argv[0] = NULL;
		while (input[++i] != NULL)
		{
			if (input[i][0] == '|')
			{
				i++;
				break ;
			}	
			if (input[i][0] == '<' || input[i][0] == '>')
			{
				if (!handleredirect(&temp, input[i], input[i + 1]))
					return (NULL);
				i++;
			}
			else
				temp->argv[j++] = ft_strdup(input[i]);
		}
		temp->argv[j] = NULL;
		temp->argc = j - 1;
		handlepaths(&temp);
		ft_lstadd_back(&out, ft_lstnew(temp));
	}
	return (out);
}

//TODO: norm, fucking norm
//TODO: constructor function || malloc protect