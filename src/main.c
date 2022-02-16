/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:39:11 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/16 15:57:58 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * The main file contains ALL things regarding shell initilization, such as
 * SHLVL and SIGHANDLE and shit like that. Because evalers are absolute 
 * dicks when it comes to checking this project.
 * 
 * I locked myself away for 3 days to get this shit done.
 * FUCK this project!
 */

/**
 * Handles signals such as "CTRL-D" or "CTRL-C"
 * 
 * @param sig The signal which was intercepted
 */
static void	ft_sig_handle(int32_t sig)
{
	// Signal: CTRL-C
	if (sig == SIGINT)
	{	
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// Signal: CTRL-'\'
	if (sig == SIGQUIT)
		return ;
}

/**
 * Constructor for an environment variable.
 * 
 * @param var The variable item to insert the envp into it.
 * @param envp An environment variable e.g: PATH=...:...
 */
static bool	ft_construct_var(t_var *var, char *envp)
{
	int32_t			i;
	const size_t	dist_to_eq = ft_strclen(envp, '=');
	const char		*specials[] = {"PWD", "SHLVL", NULL};
	char			*value;

	i = 0;
	var->key = ft_substr(envp, 0, dist_to_eq);
	if (!var->key)
		return (false);
	value = envp + dist_to_eq + 1; // +1 to skip =
	var->value = ft_substr(value, 0, ft_strlen(value));
	if (!var->value)
	{
		free(var->key);
		return (false);
	}
	var->hidden = false;
	var->unset = true; // For every var assume you can unset.
	while (specials[i]) // Unless for specials we secretly still store them :P
	{
		if (ft_strncmp(var->key, specials[i], UINT8_MAX) == 0)
			var->unset = false;
		i++;
	}
	return (true);
}

/**
 * Creates the environment pointer for the shell.
 * 
 * @param env Our environment pointer.
 * @param envp The one from main.
 * @return True or false if it managed to allocate or insert  
 */
static bool	ft_create_env(t_list **env, char **envp)
{
	int32_t	i;
	t_var	*var;
	t_list	*entry;

	i = -1;
	while (envp[++i])
	{
		var = malloc(sizeof(t_var));
		if ((var) && ft_construct_var(var, envp[i]))
		{
			entry = ft_lstnew(var);
			if (entry)
			{
				ft_lstadd_back(env, entry);
				continue ;
			}
		}
		free(var);
		return (false);
	}
	return (true);
}

/**
 * Sets up those stupid variables.
 * 
 * @param env The environment variable of our shell.
 * @param SHPath The current shell path to this instance.
 * @return Some shit got fucked, or malloc failed, will return false or true.
 */
static bool	ft_set_env_vars(t_list *env, char *SHPath)
{
	int32_t		shlvl;
	char		*shlvl_str;
	const t_var	*lvl = ft_env_get(env, "SHLVL");

	// TODO: Check how to actually deal with this garbage, for now just fail, have not tested with bash.
	// Im refering to the fact that what if shell is unset, what error do we give back ?
	if (!lvl || !ft_env_set(env, "SHELL", SHPath))
		return (false);
	shlvl = ft_atoi(lvl->value) + 1; // Go up one shell level
	if (shlvl < 0) // TODO: We shouldn't reach this point, only in debugger or if some mad lad set this as their default shell xddd
		return (false);
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return (false);
	return (ft_env_set(env, "SHLVL", shlvl_str));
}

/**
 * Entry point of the shell.
 * 
 * @param argc Argument count.
 * @param argv Argument values.
 * @param envp Environment pointer variable.
 * @return Exit code of the shell itself.
 */
int32_t	main(int argc, char **argv, char **envp)
{
	t_list	*env;

	env = NULL;
	rl_catch_signals = false;
	signal(SIGINT, ft_sig_handle);
	signal(SIGQUIT, ft_sig_handle);
	g_shell.stdin_fd = dup(STDIN_FILENO);
	g_shell.stdout_fd = dup(STDOUT_FILENO);
	if (g_shell.stdin_fd == -1 || g_shell.stdout_fd == -1)
	{
		ft_error(-1, "shell", NULL);
		exit(EXIT_FAILURE);
	}
	if (!ft_create_env(&env, envp) || !ft_set_env_vars(env, argv[0]))
	{
		ft_putendl_fd("shell: failed to initilize envs!\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_shell(env);
	close(g_shell.stdin_fd);
	close(g_shell.stdout_fd);
	exit(EXIT_SUCCESS);
}
