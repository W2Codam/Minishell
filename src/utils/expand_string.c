/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_string.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 12:24:28 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/01/27 12:56:09 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

/**
 * Takes a string with potential environment variables
 * in it and expands them.
 * 
 * @param str 
 * @return char* 
 */
char	*ft_expand_string(const char *str)
{
	return (ft_strdup(str));
}
