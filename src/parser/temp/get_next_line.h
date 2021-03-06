/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 21:05:41 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/22 21:05:43 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define MAX_FD 1024
# define BUFFER_SIZE 100

char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *src);
char	*fts_strjoin(char *s1, char *s2);

void	*ft_memmove(void *dst, const void *src, size_t len);

size_t	fts_strlen(const char *str);

static struct s_static_vars{
	char	*files[MAX_FD];
	char	buf[BUFFER_SIZE + 1];

} s_var;

#endif