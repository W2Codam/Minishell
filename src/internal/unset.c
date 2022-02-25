/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:32 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/25 17:28:51 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Unsets multiple variables
 * Does not work if the first character is not a letter
 * 
 * @param argc 
 * @param argv 
 * @return int32_t 
 */
int32_t	ft_unset(int argc, char **argv)
{
	t_var	*env;

	if (argc == 1)
	{
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (g_shell->child == 0)
		return (EXIT_SUCCESS);
	argv++;
	while (*argv)
	{	
		if (ft_isdigit(*argv[0]) || !ft_isvalidkey(*argv))
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(*argv, STDERR_FILENO);
			ft_putendl_fd(": invalid parameter name", STDERR_FILENO);
			argv++;
			continue ;
		}
		env = ft_env_get(*argv);
		if (!env)
		{
			argv++;
			continue ;
		}
		env->hidden = true;
		argv++;
	}
	return (EXIT_SUCCESS);
}

//TODO: norm