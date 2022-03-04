/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:25 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/03/04 17:51:07 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printfunc(char *str)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
}

static void	ft_exportprintevn(void)
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

static void	addenvutil(char **temp_arr, t_var *cpy, bool append)
{
	char	*old;

	if (!temp_arr[1])
	{
		free(temp_arr[0]);
	}
	else if (!append)
	{
		free(cpy->value);
		cpy->value = ft_strdup(temp_arr[1]);
	}
	else
	{
		old = cpy->value;
		cpy->value = ft_strjoin(cpy->value, temp_arr[1]);
		free(old);
	}
}

static void	addenv(char **temp_arr)
{
	t_var	*cpy;
	bool	append;

	append = false;
	if (temp_arr[0][ft_strlen(*temp_arr) - 1] == '+')
	{
		temp_arr[0][ft_strlen(*temp_arr) - 1] = 0;
		append = true;
	}
	cpy = ft_env_get(temp_arr[0]);
	if (!cpy)
	{
		if (!ft_env_add(temp_arr[0], temp_arr[1]))
			free(temp_arr[0]);
	}
	else
		addenvutil(temp_arr, cpy, append);
	free(temp_arr);
}

int32_t	ft_export(int argc, char **argv)
{
	char	**temp_arr;

	argv++;
	if (g_shell->child == 0)
		return (EXIT_SUCCESS);
	if (argc == 1)
		return (ft_exportprintevn(), EXIT_SUCCESS);
	while (*argv)
	{
		temp_arr = ft_split(*argv, '=');
		if (!temp_arr)
			return (set_exit_failure());
		if (ft_isdigit(temp_arr[0][0]) || !ft_isvalidkey(temp_arr[0]))
		{
			printfunc(*argv++);
			continue ;
		}
		addenv(temp_arr);
		argv++;
	}
	return (EXIT_SUCCESS);
}
