/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 16:11:16 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/01/26 17:51:54 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

// TODO: Edgecase, pwd when ur in directory that got deleted!
int32_t	ft_pwd(int32_t argc, char **argv, char **envp)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, sizeof(buff)))
	{
		write(STDOUT_FILENO, buff, sizeof(buff));
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
