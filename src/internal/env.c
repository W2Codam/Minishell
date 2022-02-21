/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:25:20 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/21 17:41:53 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_env(int argc, char **argv, t_list *env)
{
	t_var	*envvar;

	if (argc > 1)
	{
		ft_putendl_fd("env: illegal option", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	while (env)
	{
		envvar = env->content;
		if (!envvar->hidden)
			printf("%s=%s\n", envvar->key, envvar->value);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
