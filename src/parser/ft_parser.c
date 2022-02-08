/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:06:03 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/08 14:37:45 by pvan-dij      ########   odam.nl         */
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

int handleallpaths(t_file *var, bool write)
{
	var->fd = ft_openfile(var->path, write);
	if (var->fd == -1)
		return (-1); // something went wrong during open
	return (0);
}

bool	handleredirect(t_cmd **temp, char *direct, char *filename)
{
	if (!filename)
		return (false);
	if (direct[0] == '<')
	{
		if (check(filename))
		{
			(*temp)->in.path = filename;
			(*temp)->in.fd = -1;
			handleallpaths(&((*temp)->in), false);
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
			handleallpaths(&((*temp)->out), true);
		}
		else
			return (false);
	}
	return (true);
}

t_cmd *constructor(t_cmd *temp, int len)
{
	temp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!temp)
		return (NULL);
	temp->argv = malloc(len * sizeof(char *));
	if (!temp->argv)
	{
		free(temp);
		return (NULL);
	}
	temp->in.fd = STDIN_FILENO;
	temp->out.fd = STDOUT_FILENO;
	return (temp);
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
		temp = constructor(temp, ft_arrlen(input));
		if (!temp)
			return (NULL); // failed malloc, free possible previous mallocs in out
		if (input[i][0] == '<' || input[i][0] == '>')
		{
			if (!handleredirect(&temp, input[i], input[i + 1]))
				return (NULL); // NULL after </> or invalid filename
			i += 2;
		}
		if (input[i][0] == '|')
		{
			temp->cmd_name = NULL;
			temp->argv[0] = NULL;
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
					return (NULL);  // NULL after </> or invalid filename
				i++;
			}
			else
				temp->argv[j++] = ft_strdup(input[i]);
		}
		temp->argv[j] = NULL;
		temp->argc = j;
		ft_lstadd_back(&out, ft_lstnew(temp));
	}
	return (out);
}

//TODO: norm, fucking norm
//TODO: constructor || mallocs || error return