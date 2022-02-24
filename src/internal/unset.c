/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:32 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/24 18:44:32 by pvan-dij      ########   odam.nl         */
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

	if (g_shell->child == 0)
		return (0);
	while (++argv)
	{
		env = ft_env_get(*argv);
		env->hidden = true;
	}
	return (0);
}
