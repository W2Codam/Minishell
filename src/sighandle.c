/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sighandle.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 19:43:37 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/01 19:43:38 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

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