/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:25 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/25 17:54:18 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// {KEY}={VALUE}

void	ft_exportprintevn(void)
{
	t_var	*cpy;

	cpy = g_shell->environ;
	while (cpy)
	{
		if (cpy->hidden)
		{
			cpy = cpy->next;
			continue ;
		}
		ft_putstr("declare -x ");
		ft_putstr(cpy->key);
		ft_putstr("=\"");
		ft_putstr(cpy->value);
		ft_putstr("\"\n");
		cpy = cpy->next;
	}
}

int32_t	ft_export(int argc, char **argv)
{
	t_var	*cpy;
	char	**temp_arr;

	if (g_shell->child == 0)
		return (0);
	if (argc == 1)
		return (ft_exportprintevn(), 0);
	argv++;
	while (*argv)
	{
		temp_arr = ft_split(*argv, '=');
		if (!temp_arr)
			return (EXIT_FAILURE);
		if (ft_isdigit(temp_arr[0][0]) || !ft_isvalidkey(temp_arr[0]))
		{
			ft_putstr_fd("export: ", STDERR_FILENO);
			ft_putstr_fd(*argv, STDERR_FILENO);
			ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
			argv++;
			continue ;
		}
		cpy = ft_env_get(temp_arr[0]);
		if (!cpy)
			ft_env_add(temp_arr[0], temp_arr[1]);
		else
		{
			free(cpy->value);
			cpy->value = ft_strdup(temp_arr[1]);
		}
		free(temp_arr);
		argv++;
	}
	return (0);
}

//TODO: norm