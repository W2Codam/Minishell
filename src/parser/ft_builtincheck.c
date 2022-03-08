/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_builtincheck.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:21:07 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/08 15:04:23 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtincheck(t_cmd **cmd)
{
	int					i;
	static const t_btin	btins[] = {
	{.str = "cd", .builtin = ft_cd},
	{.str = "echo", .builtin = ft_echo},
	{.str = "env", .builtin = ft_env},
	{.str = "export", .builtin = ft_export},
	{.str = "pwd", .builtin = ft_pwd},
	{.str = "unset", .builtin = ft_unset},
	{.str = "exit", .builtin = ft_exit},
	};

	i = 0;
	while (i < (int)(sizeof(btins) / sizeof(t_btin)))
	{
		if (ft_strcmp(btins[i].str, (*cmd)->cmd_name))
		{
			(*cmd)->builtin = btins[i].builtin;
			return ;
		}
		i++;
	}
}
