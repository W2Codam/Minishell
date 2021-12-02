/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 13:23:11 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/02 14:05:54 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

void	handle(int sig)
{
	if (sig == SIGINT)
	{	
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int32_t	main(void)
{
	char				*s;

	rl_catch_signals = false;
	signal(SIGINT, handle);
	signal(SIGQUIT, handle);
	while (true)
	{
		s = readline(TITLE);
		if (s == NULL)
			exit(0);
		if (ft_strnstr(s, "exit", 4))
			break ;
		if (*s != 0)
			add_history(s);
		free(s);
	}
	exit(EXIT_SUCCESS);
}
