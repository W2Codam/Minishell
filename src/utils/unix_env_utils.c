/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_env_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 21:46:36 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/21 14:38:01 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Sets an environment variable to a specific value.
 * 
 * @param envp The environment variables.
 * @param var The variable to update.
 * @param val The new value.
 * @return Wether it succeeded in setting the variable or not.
 */
bool	ft_env_add(t_list **envp, char *key, char *value)
{
	t_var	*newvar;
	t_list	*entry;

	if (!key || !value)
		return (false);
	newvar = malloc(sizeof(t_var));
	newvar->hidden = false;
	newvar->unset = true;
	newvar->key = key;
	newvar->value = value;
	entry = ft_lstnew(newvar);
	if (!newvar->key || !newvar->value)
	{
		free(newvar);
		free(entry);
		return (false);
	}
	ft_lstadd_back(envp, entry);
	return (true);
}

/**
 * Sets an environment variable to a specific value.
 * 
 * @param envp The environment variables.
 * @param var The variable to update.
 * @param val The new value, strdups it.
 * @return Wether it succeeded in setting the variable or not.
 */
bool	ft_env_set(t_list **envp, t_var *var, char *value)
{
	char	*new_val;

	if (!var || !value)
		return (false);
	new_val = ft_strdup(value);
	if (!new_val)
		return (false);
	free(var->value);
	var->value = new_val;
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
t_var	*ft_env_get(t_list *envp, char *key)
{
	size_t	keylen;
	t_list	*env_cpy;
	t_var	*variable;

	if (!key || !envp)
		return (false);
	env_cpy = envp;
	while (env_cpy)
	{
		variable = env_cpy->content;
		keylen = ft_strlen(variable->key);
		if (ft_strncmp(variable->key, key, keylen) == 0)
			return (variable);
		env_cpy = env_cpy->next;
	}
	return (variable);
}

static bool	ft_copy_entry(char *entry, t_var *variable)
{
	char			*temp;
	const size_t	keylen = ft_strlen(variable->key);
	const size_t	vallen = ft_strlen(variable->value);

	temp = malloc(keylen + 1 + vallen);
	if (!temp)
		return (false);
	memmove(temp, variable->key, keylen);
	temp[keylen] = '=';
	memmove(temp + 1 + keylen, variable->value, vallen);
	entry = temp;
	return (true);
}

/**
 * Converts the linked list into a classical char** array.
 * On malloc fail, NULL is returned
 * 
 * @param envp The environment pointer.
 * @return On malloc fail, NULL is returned
 */
char	**ft_env_get_arr(t_list *envp)
{
	int32_t	i;
	int32_t	x;
	t_var	*variable;
	t_list	*envp_cpy;
	char	**output;

	i = 0;
	x = 0;
	envp_cpy = envp;
	output = (char **)calloc(ft_lstsize(envp) + 1, sizeof(char *));
	if (!output)
		return (NULL);
	while (envp_cpy)
	{
		variable = envp_cpy->content;
		if (!variable->hidden && !ft_copy_entry(output[i++], variable))
		{
			while (output[x] != NULL)
				free(output[x++]);
			return (NULL);
		}
		envp_cpy = envp_cpy->next;
	}
	return (output);
}

