/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stringexpand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:38:16 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/11 17:33:13 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expandenv(char *cmd, t_list *envp)
{
	t_var	*temp;
	char	*out;
	bool	found;

	found = false;
	while (envp && found == false)
	{
		temp = envp->content;
		if (!ft_strncmp(cmd + 1, temp->key, ft_strlen(cmd + 1)))
			found = true;
		envp = envp->next;
	}
	if (found == false || temp->unset == true)
		return ("");
	return (temp->value);
}

int countchar(char *str, char c)
{
	int i;

	i = 0;
	while (*str)
	{
		if *str == c
			i++;
		str++:
	}
	return (i);
}

int	findnext(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"' || arg[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char **findenvars(char *arg, t_list *envp)
{
	char	**out;
	int		i;
	int		next;

	out = (char **)malloc(sizeof(char *) * countchar(arg, '$') + 1)
	i = 0;
	while (*arg)
	{
		if (*arg == '$')
		{
			next = findnext(arg)
			out[i++] = expandenv(ft_substr(arg, 0, next));
		}
		arg++;
	}
	out[i] = NULL;
	return (out);
}

void	expandshit(t_qoute *cmd, char *s, char **envar)
{
	const char	qt[2] = {'\"', '\''};
	int			state;
	char		*save;

	save = s;
	for (int i = 0; envar[i]; i++)
	{
		printf("%s\n", envar[i]);
	}
	
}

t_qoute	*ft_stringexpand(char *in, t_list *envp)
{
	t_qoute	*out;
	int		i;

	out = splitting(in);
	i = 0;
	while (out[i].arg != NULL)
	{
		if (ft_strchr(out[i].arg, '\'') || ft_strchr(out[i].arg, '\"') \
			|| ft_strchr(out[i].arg, '$'))
			expandshit(&out[i], out[i].arg, findenvars(out[i].arg, envp));
		else
			out[i].qouted = false;
		i++;
	}
	for (int i = 0; out[i].arg; i++)
		printf("%s\n", out[i].arg);
	exit(0);
	return (out);
}
