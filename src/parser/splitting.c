/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 17:48:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/15 15:15:32 by pvan-dij      ########   odam.nl         */
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
		printf("unclosed qoute\n");
	return (words);
}

char	**splitting(char *in)
{
	char		**out;
	char		*save;
	int			state;
	int			i;

	save = in;
	i = 0;
	state = -1;
	out = (char **)malloc(sizeof(char *) * (countargs(in) + 1));
	while (*in++ != '\0')
	{

		if (*in == '\'' || *in == '\"')
			state = selectstate(*in, state);
		if ((state < 0 && *in == ' ') || !*(in + 1))
		{
			if (!*(in + 1))
				in++;
			out[i++] = ft_substr(save, 0, (in - save));
			save = in;
			save++;
		}
	}
	out[i] = NULL;
	return (out);
}

// TODO: mallocs lol get fucked