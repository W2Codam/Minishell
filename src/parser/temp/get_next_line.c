/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 21:05:50 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/03/04 18:07:06 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*stringcircumcise(char *files, char *out)
{
	int	i;

	i = 0;
	while (files[i] != '\n' && files[i])
		i++;
	out = ft_substr(files, 0, i + 1);
	if (!out)
		return (NULL);
	ft_memmove(files, files + i + 1, (fts_strlen(files) - i));
	return (out);
}

static int	checknl(char *buf)
{	
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*helper(char **files, char *out, char *buf)
{
	*files = fts_strjoin(*files, buf);
	out = *files;
	*files = NULL;
	if (!*out)
		return (NULL);
	return (out);
}

char	*get_next_line(int fd)
{
	int			bread;
	char		*out;

	out = NULL;
	if (fd < 0 || fd > MAX_FD || read(fd, s_var.buf, 0) < 0)
		return (NULL);
	if (checknl(s_var.files[fd]))
		return (stringcircumcise(s_var.files[fd], out));
	bread = 1;
	while (bread > 0)
	{
		bread = read(fd, s_var.buf, BUFFER_SIZE);
		if (bread < 0)
			return (NULL);
		s_var.buf[bread] = 0;
		if (bread == 0)
			break ;
		s_var.files[fd] = fts_strjoin(s_var.files[fd], s_var.buf);
		if (checknl(s_var.files[fd]))
			return (stringcircumcise(s_var.files[fd], out));
	}
	if (s_var.files[fd])
		return (helper(&s_var.files[fd], out, s_var.buf));
	return (NULL);
}
