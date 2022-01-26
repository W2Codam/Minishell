/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sighandle.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 19:43:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/01/26 16:25:17 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

/**
 * Handles Ctrl + c, which is SIGINT
 * 
 * @param sig 
 */
void	sig_handle(int sig)
{
	if (sig == SIGINT)
	{	
		write(1, "\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	exitout(char *s)
{
	if (s == NULL)
		write(1, "\x1b[A\x1b[15Cexit\n", 13);
	else
		write(1, "exit\n", 5);
}
