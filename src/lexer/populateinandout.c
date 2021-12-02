/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   populateinandout.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 15:27:42 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/02 16:38:35 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

char	*find_in(char *s, t_cmd *nt)
{
	char	*temp;
	int		i;
	int		j;

	temp = strchr(s, '<');
	i = 0;
	if (temp)
	{
		while (!(ft_isalnum(temp[i]) || temp[i] == '.' || temp[i] == '/'))
			i++;
		j = i;
		while (temp[j] && temp[j] != ' ')
			j++;
		nt->in.path = ft_substr(temp, i, j - i);
	}
	else
	{
		nt->in.fd = STDIN_FILENO;
		nt->in.path = NULL;
	}
	return (s);
}

char	*find_out(char *s, t_cmd *nt)
{
	char	*temp;
	int		i;
	int		j;

	temp = strchr(s, '>');
	i = 0;
	if (temp)
	{
		while (!(ft_isalnum(temp[i]) || temp[i] == '.' || temp[i] == '/'))
			i++;
		j = i;
		while (temp[j] && temp[j] != ' ')
			j++;
		nt->out.path = ft_substr(temp, i, j - i);
	}
	else
	{
		nt->out.fd = STDOUT_FILENO;
		nt->out.path = NULL;
	}
	return (s);
}

char	*remove_in(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '<')
		i++;
	j = i + 1;
	while (s[j] == ' ')
		j++;
	while (s[j] != ' ' && s[j])
		j++;
	s = ft_strjoin(ft_substr(s, 0, i), ft_substr(s, j + 1, ft_strlen(s) - j));
	return (s);
}

char	*remove_out(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '>')
		i++;
	j = i + 1;
	while (s[j] == ' ')
		j++;
	while (s[j] != ' ' && s[j])
		j++;
	s = ft_strjoin(ft_substr(s, 0, i), ft_substr(s, j, ft_strlen(s) - j));
	return (s);
}

/**
 * Finds in and out redirects and updates them in the cmd table. 
 * Return s which in this case is one command, 
 * which is defined as a line of text between any of these:
 * 		The start of the input and the end of the input.
 * 		The start of the input and a pipe.
 * 		Two pipes.
 * 		A pipe and the end of the input.
 * 		
 * 
 * @param s 
 * @param nt 
 * @return char* 
 */
char	*find_inout(char *s, t_cmd *nt)
{
	find_in(s, nt);
	find_out(s, nt);
	if (nt->in.path)
		s = remove_in(s);
	if (nt->out.path)
		s = remove_out(s);
	return (s);
}

// TODO: remove mallocs where possible and handle the ones left over