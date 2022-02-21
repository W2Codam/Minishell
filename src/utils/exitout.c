/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exitout.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:00:58 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/21 17:07:55 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exitout(char *s)
{
	if (s == NULL)
		write(1, "\x1b[A\x1b[18Cexit\n", 13);
	else
		write(1, "exit\n", 5);
}
