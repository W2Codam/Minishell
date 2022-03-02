/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stringexpand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:38:16 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/02 21:25:44 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//expand giver envar, "" on invalid/nonexisten var
static char	*expandenv(char *cmd)
{
	t_var	*temp;

	temp = ft_env_get(cmd);
	if (!temp || (temp->hidden && temp->key[0] != '?'))
		return (free(cmd), ft_strdup(""));
	free(cmd);
	return (ft_strdup(temp->value));
}

/**
 * Expands all the environment variables present in arg regardless of validity
 * 
 * @param arg The argument
 * @param envp Environment pointer
 * @return char** Array of all the expanded envars, NULL terminated
 */
char	**findenvars(char *arg)
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
			out[i++] = expandenv(ft_substr(arg + 1, 0, next));
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
	free(*cmd);
	*cmd = save;
}

bool	checkinvalid(char *str)
{	
	int			i;
	const char	*arr[] = {
		"\"<<\"", "\'<<\'"
		"\">>\"", "\'>>\'"
		"\"|\"", "\'|\'"
		"\">\"", "\'>\'"
		"\"<\"", "\'<\'",
		NULL
	};

	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(str, arr[i], ft_strlen(arr[i])) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

/**
 * Remove qoutes and expand environment variable
 * 
 * @param in The cmd typed by user
 * @param envp env pointer
 * @return the expanded string
 */
char	**ft_stringexpand(char *in)
{
	char	**out;
	char	**temp;
	char	*new;
	int		i;

	i = 0;
	out = splitting(in, i, -1);
	while (out && out[i] != NULL)
	{
		if ((ft_strchr(out[i], '\'') || ft_strchr(out[i], '\"') \
			|| ft_strchr(out[i], '$')) || !checkinvalid(out[i]))
		{
			temp = findenvars(out[i]);
			new = (char *)malloc(ft_strlen(out[i]) + arr_strlen(temp) + 1);
			if (!new)
				return (ft_cleanup(temp), ft_cleanup(out), NULL);
			expandshit(&out[i], out[i], new, temp);
			ft_cleanup(temp);
		}
		i++;
	}
	return (out);
}
