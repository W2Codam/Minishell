/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 17:48:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/15 16:39:30 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		}
	}
	if (state >= 0)
		ft_putendl("Unclosed qoute\n");
	return (words);
}

char	**splitting(char *in, int i)
{
	char **const	out = (char **)malloc(sizeof(char *) * (countargs(in) + 1));
	char			*save;
	int				state;

	if (!out)
		return (NULL);
	save = in;
	state = -1;
	while (*in++ != '\0')
	{
		if (*in == '\'' || *in == '\"')
			state = selectstate(*in, state);
		if ((state < 0 && *in == ' ') || !*(in + 1))
		{
			if (!*(in + 1))
				in++;
			out[i++] = ft_substr(save, 0, (in - save));
			if (!out[i - 1])
				return (NULL); //protect previous mallocs
			save = in;
			save++;
		}
	}
	return (out[i] = NULL, out);
}

// TODO: mallocs lol get fucked