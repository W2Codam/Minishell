/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lexer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 18:06:05 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/15 13:52:21 by pvan-dij      ########   odam.nl         */
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
		if (cmd[0] == '>' || cmd[0] == '<' || cmd[0] == '|')
			return (false);
		if (isalnum(cmd[0]))
			return (false);
	}
	else if (len == 2)
	{
		if (ft_strncmp(cmd, "<<", 2) || ft_strncmp(cmd, ">>", 2))
			return (false);
		if ((cmd[0] == '$' && isalnum(cmd[0])) || \
			((isalnum(cmd[0]) && isalnum(cmd[1]))))
			return (false);
	}
	return (false);
}

/**
 * Verifies the validity of the tokens provided by the given string input
 * 
 * @param input The given string input.
 * @return NULL on fail or valid command structure, should be passed to the
 * parser for verification.
 */
t_list	*ft_lexer(char *input, t_list *envp)
{
	char	**cmds;
	int		i;

	cmds = ft_stringexpand(input, envp);
	i = 0;
	while (cmds[i])
	{
		if (ft_tokencheck(cmds[i]))
		{
			printf("bad token\n"); //testing purposes
			return (NULL);
		}
		i++;
	}
	return (ft_parser(cmds, envp));
}

// echo HEY | tr 'A-Z' 'a-z' <= Perfectly valid!
// podufhiowuhfouiwf <= Still valid, parser will complain!
// wqdqwd | tr lol <= In terms of structure, valid however again, parser fail.
// echo HEY > input.txt < grep h // Technically valid, executor will fail.

//check for valid tokens: |, >, <, >>, << 