/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stringexpand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:38:16 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/15 21:00:40 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//expand giver envar, "" on invalid/nonexisten var
static char	*expandenv(char *cmd, t_list *envp)
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

/**
 * Expands all the environment variables present in arg regardless of validity
 * 
 * @param arg The argument
 * @param envp Environment pointer
 * @return char** Array of all the expanded envars, NULL terminated
 */
static char	**findenvars(char *arg, t_list *envp)
{
	char		**out;
	const int	dollars = countchar(arg, '$');
	int			i;
	int			next;

	if (dollars == 0)
		return (NULL);
	out = (char **)malloc(sizeof(char *) * dollars + 1);
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

/**
 * Replaces the cmd with a new version which includes expanded
 * environment variables and removal of extraneous qoutes
 * 
 * @param cmd pointer to the cmd
 * @param s copy of cmd to iterate over
 * @param envar array of expanded environment variables
 */
static void	expandshit(char **cmd, char *s, char *out, char **envar)
{
	const char	qt[2] = {'\"', '\''};
	int			state;
	char		*save;

	state = -1;
	save = out;
	while (*s)
	{
		if ((*s == '\'' || *s == '\"') && state == -1)
			state = selectstate(*s++, state);
		else if (*s == '$' && (qt[state] == '\"' || state == -1))
			addenvar(&s, &out, *envar++);
		else if (*s == '$' && qt[state] == '\'')
			moveenvarpointer(&s, &out, *envar++);
		else if (state >= 0 && *s == qt[state])
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
 * @return the expanded string
 */
char	**ft_stringexpand(char *in, t_list *envp)
{
	char	**out;
	char	**temp;
	char	*new;
	int		i;

	i = 0;
	out = splitting(in, i, -1);
	while (out && out[i] != NULL)
	{
		if (ft_strchr(out[i], '\'') || ft_strchr(out[i], '\"') \
			|| ft_strchr(out[i], '$'))
		{
			temp = findenvars(out[i], envp);
			new = (char *)malloc(ft_strlen(out[i]) + arr_strlen(temp) + 1);
			if (!new)
				return (NULL); // clean up possible previous mallocs
			expandshit(&out[i], out[i], new, temp);
		}
		i++;
	}
	return (out);
}
