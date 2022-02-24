/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:25 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/24 18:55:26 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// {KEY}={VALUE}
int32_t	ft_export(int argc, char **argv)
{
	if (g_shell->child == 0)
		return (0);
	printf("main thread: %d\n", g_shell->child);
	return (0);
}
