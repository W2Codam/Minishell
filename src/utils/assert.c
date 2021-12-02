/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assert.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 18:27:22 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/02 12:02:50 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

void	ft_assert(const char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
}
