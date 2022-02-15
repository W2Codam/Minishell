/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:32 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/15 13:26:14 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Unsets multiple variables
 * Does not work if the first character is not a letter
 * 
 * @param argc 
 * @param argv 
 * @param env 
 * @return int32_t 
 */
int32_t	ft_unset(int argc, char **argv, t_list *env)
{
	t_var	*envvar;

	if (argc == 1)
	{
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (++argv)
	{
		while (env)
		{
			envvar = env->content;
			if (ft_strncmp(*argv, envvar->key, PATH_MAX) && !envvar->hidden)
				envvar->unset = true;
			env = env->next;
		}
		argv++;
	}
	return (EXIT_SUCCESS);
}
