/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 12:51:48 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/24 18:54:25 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_pwd(int argc, char **argv)
{
	char	buf[PATH_MAX];

	if (!getcwd(buf, sizeof(buf)))
		return (EXIT_FAILURE);
	ft_putendl_fd(buf, 1);
	return (0);
}
