/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:39:11 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/24 12:33:55 by lde-la-h      ########   odam.nl         */
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
void	ft_sig_handle(int32_t sig)
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
	return (false);
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
	char		*key;
	char		*val;
	size_t		equ;

	while (*envp)
	{
		equ = ft_strclen(*envp, '=');
		key = ft_substr(*envp, 0, equ);
		val = ft_strdup(*envp + equ + 1);
		if (!ft_env_add(env, key, val))
			return (false);
		envp++;
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
static bool	ft_set_env_vars(t_list **env, char *shellpath)
{
	int32_t			shlvl_val;
	t_var *const	shlvl = ft_env_get(*env, "SHLVL");
	t_var *const	shell = ft_env_get(*env, "SHELL");

	if (!shlvl || !shell)
		return (false);
	shlvl_val = ft_atoi(shlvl->value) + 1;
	if (shlvl_val <= 0)
		return (false);
	if (!ft_env_set(env, ft_env_get(*env, "SHLVL"), ft_itoa(shlvl_val)))
		return (false);
	if (!ft_env_set(env, ft_env_get(*env, "SHELL"), shellpath))
		return (false);
	return (true);
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
	t_list			*env;
	struct termios	raw;

	env = NULL;
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	rl_catch_signals = false;
	signal(SIGINT, ft_sig_handle);
	signal(SIGQUIT, ft_sig_handle);
	if (!ft_create_env(&env, envp) || !ft_set_env_vars(&env, argv[0]))
	{
		ft_putendl_fd("shell: failed to initilize envs!\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	g_shell.environ = env;
	ft_shell();
	exit(EXIT_SUCCESS);
}
