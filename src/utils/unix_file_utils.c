/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unix_file_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 19:56:32 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/01/27 12:46:43 by lde-la-h      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

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
int32_t	ft_openfile(char *path, bool isoutput)
{
	int32_t	fd;

	if (isoutput)
	{
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IROTH);
	}
	else
	{
		fd = open(path, O_RDONLY);
	}
	if (fd < 0)
		ft_assert("Unable to open file");
	return (fd);
}
