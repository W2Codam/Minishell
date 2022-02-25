/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:25:20 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/24 19:21:45 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_env(int argc, char **argv)
{
	const t_var	*envcpy = g_shell->environ;

	while (envcpy)
	{
		if (!envcpy->hidden)
			printf("%s=%s\n", envcpy->key, envcpy->value);
		envcpy = envcpy->next;
	}
	return (EXIT_SUCCESS);
}
