/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 17:25:16 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/03/02 17:52:10 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int32_t	ft_exit(int argc, char **argv)
{
	if (g_shell->child == 0)
		return (EXIT_SUCCESS);
	if (argc > 2)
	{
		ft_putendl_fd("cd: Too many arguments.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (argv[1] && ft_strisnum(argv[1]) == 0)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(ft_atoi(argv[1]));
}
