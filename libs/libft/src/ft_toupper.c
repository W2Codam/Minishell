/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:03:41 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/10/26 18:54:18 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_i32	ft_toupper(t_i32 c)
{
	if (ft_islower(c))
		return (c - 32);
	return (c);
}
