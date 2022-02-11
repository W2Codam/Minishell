/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   splitting.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 17:48:12 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/11 13:07:29 by pvan-dij      ########   odam.nl         */
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
	while (*s != 0)
	{
		if (*s != ' ')
			words++;
		while ((*s != ' ' || state >= 0) && *s)
		{
			if (*s == '\'' || *s == '\"')
				state = selectstate(*s, state);
			s++;
		}
		s++;
	}
	if (state >= 0)
		printf("unclosed qoute");
	printf("%d\n", words);
	return (words);
}

t_qoute	*splitting(char *in)
{
	t_qoute		*out;
	char		*save;
	int			state;
	int			i;

	save = in;
	i = 0;
	state = -1;
	out = (t_qoute *)malloc(sizeof(t_qoute) * (countargs(in) + 1));
	while (*in)
	{
		if (*in == '\'' || *in == '\"')
			state = selectstate(*in, state);
		if ((state < 0 && *in == ' ') || !*(in + 1))
		{
			if (!*(in + 1))
				in++;
			out[i++].arg = ft_substr(save, 0, (in - save));
			save = in;
			save++;
		}
		in++;
	}
	out[i].arg = NULL;
	return (out);
}

// TODO: mallocs lol get fucked