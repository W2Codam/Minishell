/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 17:48:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/04 20:38:10 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Selects state based on c. Return -1 if we're exiting a qoute,
 * 1 for ' and 0 for "
 * 
 * @param c " or ' 
 * @param state State variable, initialized to -1, changed afterwards
 * @return The new value of state
 */
int	selectstate(char c, int state)
{
	const char	qt[2] = {'\"', '\''};

	if (state >= 0 && c == qt[state])
		state = -1;
	else if (state == -1)
	{
		if (c == '\'')
			state = 1;
		else
			state = 0;
	}
	return (state);
}

int	countargs(char *s)
{
	int			state;
	int			words;

	words = 0;
	state = -1;
	while (*s++ != 0)
	{
		if (*s != ' ')
			words++;
		while ((*s != ' ' || state >= 0) && *s)
		{
			if (*s == '\'' || *s == '\"')
				state = selectstate(*s, state);
			s++;
			if (*s == 0)
				return (words++, words);
		}
	}
	if (state >= 0)
		ft_putendl("Unclosed qoute\n");
	return (words);
}

/**
 * Splits up string into array while respecting qoutes
 * 
 * @param in input string
 * @param i lolnorm
 * @param state lolnorm
 * @return char** 
 */
char	**splitting(char **out, char *in, int i, int state)
{
	char			*save;

	while (*in == ' ')
		in++;
	save = in;
	while (*in != '\0')
	{
		if (*in == '\'' || *in == '\"')
			state = selectstate(*in, state);
		if ((state < 0 && *in == ' ') || !*(in + 1))
		{
			if (*in == ' ' && *(in + 1) == 0)
				*in = 0;
			else if (*(in + 1) == 0)
				in++;
			out[i++] = ft_substr(save, 0, (in - save));
			if (!out[i - 1])
				return (ft_cleanup(out), NULL);
			while (*in + 1 && *in == ' ')
				in++;
			save = in;
			continue ;
		}
		in++;
	}
	return (out[i] = NULL, out);
}
