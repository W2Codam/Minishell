/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 13:23:11 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/02 14:23:39 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

int32_t	main(int32_t argc, char **argv, char **envp)
{
	char				*s;

	rl_catch_signals = 0;
	SHUTFUCK(argc);
	SHUTFUCK(argv);
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
	while (true)
	{
		s = readline(TITLE);
		if (s == NULL || ft_strnstr(s, "exit", 4))
			break ;
		if (*s == 0)
			continue ;
		if (!lexer(s, envp))
			add_history(s);
		free(s);
	}
	exit(EXIT_SUCCESS);
}
