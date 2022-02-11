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

//expand giver envar, "" on invalid/nonexisten var
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
	if (found == false || temp->hidden == true)
		return ("");
	return (temp->value);
}

//count occurences of char in string
int countchar(char *str, char c)
{
	int i;

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

//make an array of all the expanded envvars in arg
char **findenvars(char *arg, t_list *envp)
{
	char	**out;
	int		i;
	int		next;

	out = (char **)malloc(sizeof(char *) * countchar(arg, '$') + 1);
	i = 0;
	while (*arg)
	{
		if (*arg == '$')
		{
			next = findnext(arg+1);
			out[i++] = expandenv(ft_substr(arg, 0, next-1), envp);
		}
		arg++;
	}
	out[i] = NULL;
	return (out);
}

int	arr_strlen(char **arr)
{
	int i;
	int out;

	i = 0;
	out = 0;
	while (arr[i])
	{
		out += ft_strlen(arr[i]);
		i++;
	}
	return (out);
}

void addenvar(char **s, char **out, char *envar)
{
	ft_memmove(*out, envar, ft_strlen(envar));
	*out += ft_strlen(*out);
	*s += findnext(*s + 1) + 1;
}

void	expandshit(t_qoute *cmd, char *s, char **envar)
{
	const char	qt[2] = {'\"', '\''};
	int			state;
	char		*save;
	char		*out;

	state = -1;
	out = (char *)malloc(ft_strlen(s) + arr_strlen(envar) + 1);
	save = out;
	while (*s)
	{
		if ((*s == '\'' || *s == '\"') && state == -1)
			state = selectstate(*s++, state);
		else if (*s == '$' && (qt[state] == '\"' || state == -1))
			addenvar(&s, &out, *envar++);
		else if (*s == qt[state])
			state = selectstate(*s++, state);
		else
			*out++ = *s++;
	}
	*out = 0;
	cmd->qouted = true;
	cmd->arg = save;
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
