/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 16:10:49 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/01/27 12:53:44 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

/**
 * Prints the environment variables.
 * 
 * According to subject no options nor arguments. Aka we just ignore them :)
 * @param argc Always 1.
 * @param argv Always 1.
 * @param envp The environement variables.
 * @return Always success.
 */
int32_t	ft_env(int32_t argc, char **argv, char **envp)
{
	SHUTFUCK(argc);
	SHUTFUCK(argv);

	while (*envp)
	{
		write(STDOUT_FILENO, *envp, ft_strlen(*envp));
		envp++;
	}
	return (EXIT_SUCCESS);
}
