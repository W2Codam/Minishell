/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_err_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 10:48:17 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/03 10:55:35 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints if errno is set, allows for overriding error message
 * if errovr is not -1 or msg is not NULL.
 * 
 * Messages are written to STDERR.
 * 
 * @param[in] errovr The error to override
 * @param[in] s Error title like in perror(...)
 * @param[in] msg The alternative message.
 */
void	ft_error(int32_t errovr, const char *s, char *msg)
{
	if (errno == errovr && (s != NULL && errovr >= 0 && msg != NULL))
	{
		write(STDERR_FILENO, s, ft_strlen(s));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, msg, ft_strlen(msg));
	}
	else
		perror(s);
}