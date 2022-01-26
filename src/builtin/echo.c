/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/26 16:10:44 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/01/26 16:38:25 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

static void	ft_print_args(int32_t argc, char **argv, bool newline)
{
	while (argc >= 3 & i < argc - 1)
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]))
		i++;
	}
}

/**
 * Main function for echo / writing to STDOUT.
 * 
 * @param argc Argument count.
 * @param argv Any type of arguments.
 * @param envp The environment variable pointer.
 * @return Standart exit code.
 */
int32_t	ft_echo(int32_t argc, char **argv, char **envp)
{
	int32_t	i;
	bool	newline;

	i = 1;
	newline = true;
	if (argc < 2)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (EXIT_SUCCESS);
	}
	if (argc > 2)
	{
		if (ft_strncmp(argv[2], "-n", 2))
			newline = false;
		if (argc < 3)
			write(STDOUT_FILENO, "", 1);
	}
	ft_print_args(argc, argv, newline);
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
