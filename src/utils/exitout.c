/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exitout.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:00:58 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/02/24 21:32:16 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exitout(char *s)
{
	if (s == NULL)
		ft_putendl("\x1b[A\x1b[18Cexit");
	else
		ft_putendl("exit");
}
