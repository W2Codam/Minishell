/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 16:10:46 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/01/26 17:48:43 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

/**
 * Changes the directory to either a relative or absolute path.
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int32_t 
 */
int32_t	ft_cd(int32_t argc, char **argv, char **envp)
{
	if (argc == 1)
		return (EXIT_SUCCESS);
	return (argc >= 2 && chdir(argv[2]) != -1);
}
