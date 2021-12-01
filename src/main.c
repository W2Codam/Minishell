/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 13:23:11 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/01 14:35:57 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

bool	checkbuiltins(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (ft_strnstr(argv[1], "echo", len))
		return (false);
}

int32_t	main(int32_t argc, char const **argv, char const **envp)
{
	SHUTFUCK(argc);
	SHUTFUCK(argv);
	SHUTFUCK(envp);
	exit(EXIT_SUCCESS);
}
