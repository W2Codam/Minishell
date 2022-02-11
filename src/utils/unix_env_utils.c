/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_env_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 21:46:36 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/11 15:37:26 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_env_cpy(t_var *var, char *buffer, size_t buffsize)
{
	size_t	len;

	memset(buffer, '\0', buffsize);
	if (var->hidden) // Hidden variables are not meant to be added.
		return ;
	len = ft_strlen(var->key);
	memmove(buffer, var->key, len);
	buffer[len++] = '=';
	len = ft_strlen(var->value);
	memmove(buffer, var->value, len);
}

/**
 * Sets an environment variable to a specific value.
 * 
 * @param envp The environment variables.
 * @param var The variable to update.
 * @param val The new value.
 * @return Wether it succeeded in setting the variable or not.
 */
bool	ft_env_set(t_list *envp, char *key, char *value)
{
	t_var	*variable;
	t_list	*envp_cpy;

	envp_cpy = envp;
	while (envp_cpy)
	{
		variable = envp_cpy->content;
		if (ft_strncmp(variable->key, key, ft_strlen(variable->key)) == 0)
		{
			free(variable->value);
			variable->value = value;
			return (true);
		}
		envp_cpy = envp_cpy->next;
	}
	return (false);
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
	t_var	*variable;
	t_list	*envp_cpy;

	envp_cpy = envp;
	while (envp_cpy)
	{
		variable = envp_cpy->content;
		if (ft_strncmp(variable->key, key, ft_strlen(variable->key)) == 0)
			return (variable);
		envp_cpy = envp_cpy->next;
	}
	return (NULL);
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
	char	**arr;
	char	temp[4096];
	t_list	*envp_cpy;

	i = 0;
	arr = malloc(ft_lstsize(envp) * sizeof(char *));
	if (!arr)
		return (NULL);
	envp_cpy = envp;
	while (envp_cpy)
	{
		ft_env_cpy(envp_cpy->content, temp, sizeof(temp));
		arr[i] = ft_strdup(temp);
		if (!arr[i])
		{
			//TODO: Free arr
			free(arr);
			return (NULL);
		}
		envp_cpy = envp_cpy->next;
	}
	return (arr);
}
