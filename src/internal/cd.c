/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:28:16 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/03/01 20:34:33 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chdir(char *path)
{
	char	*tmp_path;
	t_var	*temp;

	if (path == NULL)
		return (EXIT_FAILURE);
	tmp_path = getcwd(NULL, -1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory.", STDERR_FILENO);
		free(tmp_path);
		return (EXIT_FAILURE);
	}
	temp = ft_env_get("OLDPWD");
	if (temp->hidden)
		temp->hidden = false;
	free(temp->value);
	temp->value = ft_strdup(tmp_path);
	free(tmp_path);
	return (EXIT_SUCCESS);
}

// Garbage CD lol
int32_t	ft_cd(int argc, char **argv)
{
	char	*path;

	if (argc > 2)
		return (ft_putendl_fd("cd: Too many arguments.", STDERR_FILENO), \
			EXIT_FAILURE);
	if (g_shell->child == 0)
		return (0);
	if (argc == 1 || ft_strncmp("~", argv[1], 1) == 0)
	{
		path = ft_env_get("HOME")->value;
		if (path == NULL)
			return (ft_putendl_fd("cd: No home directory.", STDERR_FILENO), \
				EXIT_FAILURE);
		return (ft_chdir(path));
	}
	if (ft_strncmp("-", argv[1], 1) == 0)
	{
		if (ft_env_get("OLDPWD")->hidden)
			return (ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO), \
				EXIT_FAILURE);
		return (ft_chdir(ft_env_get("OLDPWD")->value));
	}
	else
		return (ft_chdir(argv[1]));
	return (EXIT_SUCCESS);
}
