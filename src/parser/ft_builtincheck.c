/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_builtincheck.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:21:07 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/24 12:30:39 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtincheck(t_cmd **cmd)
{
	int					i;
	static const t_btin	btins[] = {
		// {.str = "cd", .builtin = ft_cd},
	{.str = "echo", .builtin = ft_echo},
		// {.str = "env", .builtin = ft_env},
		// {.str = "export", .builtin = ft_export},
		// {.str = "pwd", .builtin = ft_pwd},
	{.str = "unset", .builtin = ft_unset},
	};

	i = 0;
	while (i < sizeof(btins) / sizeof(t_btin))
	{
		if (!ft_strncmp((*cmd)->cmd_name, btins[i].str, \
				ft_strlen(btins[i].str)))
		{
			(*cmd)->builtin = btins[i].builtin;
			return ;
		}
		i++;
	}
}
