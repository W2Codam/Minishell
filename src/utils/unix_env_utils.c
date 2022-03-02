/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_env_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 21:46:36 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 15:59:11 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*ft_lastvar(t_var *varr, size_t *size)
{
	size_t	i;

	i = 0;
	while (varr)
	{
		if (!varr->next)
			break ;
		varr = varr->next;
		i++;
	}
	if (size)
		*size = i;
	return (varr);
}

/**
 * Sets an environment variable to a specific value.
 * 
 * @param envp The environment variables.
 * @param var The variable to update.
 * @param val The new value.
 * @return Wether it succeeded in setting the variable or not.
 */
bool	ft_env_add(char *key, char *value)
{
	t_var	*newval;
	t_var	*last;

	if (!key || !value)
		return (false);
	newval = malloc(sizeof(t_var));
	if (!newval)
		return (false);
	newval->key = key;
	newval->value = value;
	newval->hidden = false;
	newval->next = NULL;
	if (!g_shell->environ)
		g_shell->environ = newval;
	else
	{
		last = ft_lastvar(g_shell->environ, NULL);
		last->next = newval;
	}
	return (true);
}

/**
 * Gets an environment variable  from a specific key.
 * 
 * @param envp The environment variables.
 * @param var The variable to update.
 * @param val The new value.
 * @return Wether it succeeded in setting the variable or not.
 */
t_var	*ft_env_get(char *key)
{
	t_var	*cpy;

	if (!key)
		return (NULL);
	cpy = g_shell->environ;
	while (cpy)
	{
		if (ft_strncmp(cpy->key, key, ft_strlen(key)) == 0)
			return (cpy);
		cpy = cpy->next;
	}
	return (NULL);
}

/**
 * Set environment variables that need to start out as hidden, to hidden = tru
 * 
 * @param starthidden char * array of the keys that need to be hidden
 */
void	ft_starthidden(const char **starthidden)
{
	t_var	*temp;

	while (*starthidden)
	{
		temp = ft_env_get((char *)*starthidden);
		temp->hidden = true;
		starthidden++;
	}
}

char	**ft_lst_to_arr(t_var *lst)
{
	int32_t		i;
	size_t		size;
	char		**arr;
	const t_var	*lstcpy = lst;

	i = 0;
	arr = (char **)ft_calloc(ft_envsize() + 1, sizeof(char *));
	while (arr && lstcpy)
	{
		if (!lstcpy->hidden)
		{
			size = ft_strlen(lstcpy->key) + 2 + ft_strlen(lstcpy->value);
			arr[i] = ft_calloc(size + 1, sizeof(char));
			if (!arr[i])
				return (ft_cleanup(arr), NULL);
			ft_strlcat(arr[i], lstcpy->key, size);
			ft_strlcat(arr[i], "=", size);
			ft_strlcat(arr[i], lstcpy->value, size);
			i++;
		}
		lstcpy = lstcpy->next;
	}
	arr[++i] = NULL;
	return (arr);
}
