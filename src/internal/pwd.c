/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/24 12:51:48 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/03/01 16:44:47 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	ft_pwd(int argc, char **argv)
{
	char	buf[PATH_MAX];

	(void)argv;
	if (argc > 1)
	{
		ft_putendl_fd("pwd: too many arguments you moron", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!getcwd(buf, sizeof(buf)))
	{
		perror("pwd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(buf, 1);
	return (0);
}
