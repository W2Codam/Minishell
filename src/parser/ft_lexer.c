/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lexer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:06:05 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/03/01 17:56:01 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_tokencheck(char *cmd)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(cmd);
	if (len == 1)
	{
		if (ft_strchr("><~|-\b", cmd[0])) //fix yo strchr
			return (false);
		if (ft_isalnum(cmd[0]))
			return (false);
		return (true);
	}
	else if (len == 2)
	{
		if ((ft_strncmp(cmd, "<<", 2) || ft_strncmp(cmd, ">>", 2)))
			return (false);
		if ((cmd[0] == '$' && ft_isalnum(cmd[1])) || \
			(ft_isalnum(cmd[0]) && ft_isalnum(cmd[1])))
			return (false);
		return (true);
	}
	else if (cmd[0] == '|' || cmd[0] == '>' || cmd[0] == '<')
		return (true);
	return (false);
}

/**
 * Verifies the validity of the tokens provided by the given string input
 * 
 * @param input The given string input.
 * @return NULL on fail or valid command structure, should be passed to the
 * parser for verification.
 */
t_list	*ft_lexer(char *input)
{
	char	**cmds;
	t_list	*temp;
	int		i;

	cmds = ft_stringexpand(input);
	if (!cmds)
		return (ft_putstr_fd("String expand error\n", STDERR_FILENO), \
			NULL);
	i = 0;
	while (cmds[i])
	{
		if (ft_tokencheck(cmds[i]))
		{
			return (ft_putstr_fd("Bad token", STDERR_FILENO), \
				ft_cleanup(cmds), NULL);
		}
		i++;
	}
	temp = ft_parser(cmds);
	ft_cleanup(cmds);
	return (temp);
}
