/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stringexpand_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 13:33:13 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/04 14:55:59 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//count occurences of char in string
int	countchar(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

//find next occurence of ' " $
int	findnext(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '?' && arg[1] == 0)
		return (1);
	if (arg[0] == '{')
	{
		while (arg[i] != '}' && arg[i])
			i++;
		return (i + 1);
	}
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"' || arg[i] == '$' || \
			(!ft_isalnum(arg[i])))
			return (i);
		i++;
	}
	return (i);
}

//length of all string in char array
int	arr_strlen(char **arr)
{
	int	i;
	int	out;

	i = 0;
	out = 0;
	if (!arr)
		return (0);
	while (arr[i])
	{
		out += ft_strlen(arr[i]);
		i++;
	}
	return (out);
}

//both of these exist because lolnorm
void	addenvar(char **s, char **out, char *envar)
{
	ft_memmove(*out, envar, ft_strlen(envar) + 1);
	*out += ft_strlen(*out);
	*s += findnext(*s + 1) + 1;
}

void	moveenvarpointer(char **s, char **out, char *envar)
{
	**out = **s;
	*out += 1;
	*s += 1;
	(void)envar;
}
