/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   assert.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 18:27:22 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/01 18:36:31 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

void	assert(const char *msg, int32_t exitcode)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(exitcode);
}
