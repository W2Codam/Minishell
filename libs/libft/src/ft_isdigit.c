/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/04 14:03:41 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/10/27 11:28:07 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isdigit(t_i32 c)
{
	return (c >= '0' && c <= '9');
}
