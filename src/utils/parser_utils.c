/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 20:35:18 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/04 12:45:22 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lolnorm
int	testpipe(char *c, int i)
{
	if (i == 0 || !c || c[0] == '|')
		return (ft_putstr_fd("Piping error\n", STDERR_FILENO), -1);
	return (i + 1);
}

t_file	*evaluate(t_file *in, t_file *out, char c)
{
	if (c == '>')
		return (out);
	return (in);
}

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
		if (!ft_strncmp(cmd, "<<", 2) || !ft_strncmp(cmd, ">>", 2))
			return (false);
	}
	return (true);
}

int	handleallpaths(t_file *var, bool write, bool append)
{
	var->fd = ft_openfile(var->path, write, append);
	if (var->fd == -1)
	{
		printf("lol");
		return (-1);
	}
	return (0);
}

//TODO: very random redirect error, uninitialized memory?