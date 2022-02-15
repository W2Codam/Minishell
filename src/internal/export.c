/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:25 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/15 15:15:19 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_modify_entry(t_list *env, char *key, char *val)
{
	t_list	*env_cpy;
	t_var	*variable;

	while (env_cpy)
	{
		variable = env_cpy->content;
		if (variable->key)
		{
			return (EXIT_SUCCESS);
		}
		env_cpy = env_cpy->next;
	}
	return (true);
}

/*
// {KEY}={VALUE}
int32_t	ft_export(int argc, char **argv, t_list *env)
{
	char	*key;
	char	*value;
	char	*equal;
	t_list	*new;
	t_var	*variable;

	if (argc == 1)
	{
		ft_putendl_fd("export: No arguments.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (++argv)
	{
		equal = ft_strchr(*argv)
		key = ft_substr(*argv, 0, ft_strclen(*agrv, '='))
		if (!*val)
		{
			free (key);
			continue ;
		}
	}
	return (EXIT_SUCCESS);
}
*/