/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_file_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 19:10:21 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/25 15:54:42 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Simplified wrapper for access to return proper boolean.
 * @param path The path to the file.
 * @param flags The flags to use for checking.
 * @returns Depending on the flag wether the condition is met or not.
 */
bool	ft_access(const char *path, int32_t flags)
{
	return (access(path, flags) != -1);
}

/**
 * Checks if the given file is a valid file to use.
 * stdin, out & err are valid, its not valid if path is null or fd < 0.
 * 
 * @param file The file to check.
 * @return Wether the file is valid or not.
 */
bool	ft_valid_file(t_file *file)
{
	if (file->fd == STDIN_FILENO || file->fd == STDOUT_FILENO || \
		file->fd == STDERR_FILENO)
		return (true);
	if (!file->path || file->fd < 0)
		return (false);
	return (ft_access(file->path, F_OK));
}

/**
 * "Opens" a file by either just opening it or if its meant to be
 * the output, aka stdout, then create it.
 * 
 * @param path The file path to open.
 * @param isoutput Is the file meant to be an output file, aka written to.
 * @return The file descriptor.
 */
int32_t	ft_openfile(char *path, bool isoutput, bool append)
{
	int32_t	fd;

	if (isoutput && append)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, \
		S_IRUSR | S_IWUSR | S_IROTH);
	else if (isoutput)
	{
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IROTH);
	}
	else
	{
		fd = open(path, O_RDONLY);
	}
	if (fd < 0 || errno)
		return (-1);
	return (fd);
}
