/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_env_utils_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 21:46:36 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/03/02 15:43:34 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_envsize(void)
{
	size_t	n;
	t_var	*cpy;

	n = 0;
	cpy = g_shell->environ;
	while (cpy)
	{
		if (!cpy->hidden)
			n++;
		cpy = cpy->next;
	}
	return (n);
}
