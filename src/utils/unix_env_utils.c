/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_env_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 21:46:36 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/24 14:52:48 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*ft_lastvar(t_var *varr)
{
	while (varr)
	{
		if (!varr->next)
			break ;
		varr = varr->next;
	}
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
		last = ft_lastvar(g_shell->environ);
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
		if (ft_strncmp(cpy->key, key, ft_strlen(cpy->key)) == 0)
			return (cpy);
		cpy = cpy->next;
	}
	return (NULL);
}
