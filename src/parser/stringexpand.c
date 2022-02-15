/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stringexpand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:38:16 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/15 13:56:54 by pvan-dij      ########   odam.nl         */
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

//make an array of all the expanded envvars in arg
char	**findenvars(char *arg, t_list *envp)
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
			next = findnext(arg + 1);
			out[i++] = expandenv(ft_substr(arg, 0, next - 1), envp);
		}
		arg++;
	}
	out[i] = NULL;
	return (out);
}

void	expandshit(char **cmd, char *s, char **envar)
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
		else if (*s == '$' && qt[state] == '\'')
			moveenvarpointer(&s, &out, *envar++);
		else if (*s == qt[state])
			state = selectstate(*s++, state);
		else
			*out++ = *s++;
	}
	*out = 0;
	*cmd = save;
}

/**
 * Remove qoutes and expand environment variable
 * 
 * @param in The cmd typed by user
 * @param envp env pointer
 * @return the expanded 
 */
char	**ft_stringexpand(char *in, t_list *envp)
{
	char	**out;
	int		i;

	out = splitting(in);
	i = 0;
	while (out[i] != NULL)
	{
		if (ft_strchr(out[i], '\'') || ft_strchr(out[i], '\"') \
			|| ft_strchr(out[i], '$'))
			expandshit(&out[i], out[i], findenvars(out[i], envp));
		i++;
	}
	return (out);
}
