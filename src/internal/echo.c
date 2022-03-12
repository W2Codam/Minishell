/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:08 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/24 12:45:09 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_args(int32_t argc, char **argv, bool newline)
{
	int32_t	i;

	i = 1;
	if (!newline)
		i++;
	while (argc >= 2 && i <= argc - 1)
	{
		ft_putstr(argv[i++]);
		ft_putchar(' ');
	}
	if (newline)
		ft_putchar('\n');
}

int32_t	ft_echo(int argc, char **argv)
{
	bool	newline;

	newline = true;
	if (argc == 1)
	{
		ft_putchar('\n');
		return (EXIT_SUCCESS);
	}
	if (argc >= 2)
	{
		if (ft_strncmp(argv[1], "-n", 2) == 0)
			newline = false;
		if (argc < 3)
			ft_putchar('\0');
	}
	ft_print_args(argc, argv, newline);
	return (EXIT_SUCCESS);
}
