/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:39:11 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/24 15:09:06 by lde-la-h      ########   odam.nl         */
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
	if (sig == SIGINT)
	{	
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}

/**
 * Creates the environment pointer for the shell.
 * 
 * @param env Our environment pointer.
 * @param envp The one from main.
 * @return True or false if it managed to allocate or insert  
 */
static bool	ft_create_env(char **envp)
{
	char		*key;
	char		*val;
	size_t		equ;

	while (*envp)
	{
		equ = ft_strclen(*envp, '=');
		key = ft_substr(*envp, 0, equ);
		val = ft_strdup(*envp + equ + 1);
		if (!ft_env_add(key, val))
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
static bool	ft_set_env_vars(char *shellpath)
{
	int32_t			shlvl_val;
	t_var *const	shlvl = ft_env_get("SHLVL");
	t_var *const	shell = ft_env_get("SHELL");

	free(shell->value);
	shell->value = ft_strdup(shellpath);
	if (!shell->value)
		return (false);
	return (true);
}

t_shell	*g_shell;

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
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	rl_catch_signals = false;
	signal(SIGINT, ft_sig_handle);
	signal(SIGQUIT, ft_sig_handle);
	g_shell = calloc(1, sizeof(t_shell));
	if (!ft_create_env(envp) || !ft_set_env_vars(argv[0]))
	{
		ft_putendl_fd("shell: failed to initilize envs!\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_shell();
	exit(EXIT_SUCCESS);
}

//TODO: builtins, norm, cleanup