/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_builtin_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/25 17:26:38 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/04 15:06:29 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_isvalidkey(char *str)
{
	while (*str)
	{
		if (ft_isalnum(*str) == false && (*str != '+' && *str + 1 != '='))
			return (false);
		str++;
	}
	return (true);
}

int	set_exit_failure(void)
{
	t_var	*temp;

	temp = ft_env_get("?");
	if (!temp)
		return (1);
	free(temp->value);
	temp->value = ft_strdup("1");
	return (1);
}
