/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:16 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/21 15:28:34 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chdir(char *path, t_list *envp)
{
	char	*tmp_path;

	if (path == NULL)
		return (EXIT_FAILURE);
	tmp_path = getcwd(NULL, -1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd("cd: No such file or directory.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_env_set(&envp, ft_env_get(envp, "OLDPWD"), tmp_path);
	fprintf(stderr, "DIR: %s\n", getcwd(NULL, -1));
	return (EXIT_SUCCESS);
}

// Garbage CD lol
int32_t	ft_cd(int argc, char **argv, t_list *env)
{
	char	*path;

	if (argc > 2)
	{
		ft_putendl_fd("cd: Too many arguments.", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (argc == 1)
	{
		path = ft_env_get(env, "HOME")->value;
		if (path == NULL)
		{
			ft_putendl_fd("cd: No home directory.", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		return (ft_chdir(path, env));
	}
	if (ft_strncmp("-", argv[1], 1) == 0)
		return (ft_chdir(ft_env_get(env, "OLDPWD")->value, env));
	if (ft_strncmp("~", argv[1], 1) == 0)
		return (ft_chdir(ft_env_get(env, "HOME")->value, env));
	else
		return (ft_chdir(argv[1], env));
	return (EXIT_SUCCESS);
}
