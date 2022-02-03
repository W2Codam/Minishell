/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: w2wizard <w2wizard@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/03 00:08:09 by w2wizard      #+#    #+#                 */
/*   Updated: 2022/02/03 22:12:58 by w2wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bash seems to be going backwards in terms of execution

// For every command, we basically make a fork.
// That fork does it shit and then returns to the parent
// Depending on the exit code we then write a corresponding
// error and continue.

// Additionally we need to then handle pipes by basically 
// creating single pipe, child direct its output to the 
// write part of the pipe, while parent reads from the pipe
// parent then redirects the read to wherever the command wanted
// to send the output to, say STDOUT or the file.

/*
	char		**arr;
	const char	*exe_path = ft_getexec(cmd->cmd_name, env);
	
	close(fds[READ]);				 // We don't need to read
	dup2(fds[WRITE], STDOUT_FILENO); // STDOUT goes into write of pipe
	arr = ft_env_get_arr(env);
	if (!arr)
	{
		write(STDERR_FILENO, "shell: memory allocation failure\n", 33);
		exit (EXIT_FAILURE);
	}
	if (cmd->builtin)
		exit(cmd->builtin(0, NULL, env));
	fprintf(stderr, "%s\n", ft_getexec(cmd->cmd_name, env));
	execve(exe_path, args, environ);
	ft_error(ENOENT, cmd->cmd_name, "command not found\n");
	if (errno == ENOENT) // Error num on missing file, re-intrept as no command.
		exit (EXIT_NOTFOUND);
	close(STDOUT_FILENO);
	exit (EXIT_FAILURE); // We don't need to free, exit takes care of that.
*/


extern char **environ;

void	ft_child(t_cmd *cmd, int32_t fds[2], t_list *env)
{
	char		**arr;
	const char	*exe_path = ft_getexec(cmd->cmd_name, env);
	
	close(fds[READ]);				 // We don't need to read
	dup2(cmd->in.fd, STDIN_FILENO);
	dup2(fds[WRITE], STDOUT_FILENO); // STDOUT goes into write of pipe
	//dup2(fds[WRITE], STDIN_FILENO); // STDOUT goes into write of pipe

	cmd->argv[0] = (char *)exe_path;
	if (cmd->argv[0])
		execve(exe_path, cmd->argv, environ);
	else
	{
		// No command.
		ft_error(ENOENT, cmd->cmd_name, "command not found\n");
		exit (EXIT_NOTFOUND);
	}
	ft_error(-1, "shell", NULL);
	close(STDOUT_FILENO);
	exit (EXIT_FAILURE); // We don't need to free, exit takes care of that.
}

/**
 * Parent job is to just direct the read end of the pipe
 * to the right file descriptor and write to it.
 * 
 * If STDOUT & no next, actually write to STDOUT
 * If STDOUT & next, write to STDIN as we wanna move it forward
 * If NOT STDOUT & write to fd.
 * 
 * @param cmds 
 * @param fds 
 * @param env 
 * @param pid 
 */
void	ft_parent(t_list *cmds, int32_t fds[2], t_list *env, pid_t pid)
{
	int32_t		exitval;
	char		buf[256] = {0}; 
	const t_cmd *cmd = cmds->content;

	// Do we need it ? I don't know but better safe than sorry.
	dup2(g_shell.stdin_fd, STDIN_FILENO);
	dup2(g_shell.stdout_fd, STDOUT_FILENO);

	close(fds[WRITE]); // We will not write to pipe out

	for (int n = 0; (n = read(fds[READ], buf, sizeof(buf))) > 0;)
			write(cmd->out.fd, buf, n); 

	if (waitpid(pid, &exitval, 0) == -1) 
		ft_error(-1, "shell", NULL);

	printf("EXIT CODE: %d\n", exitval);
	close(fds[READ]); // We finished doing our job!
}

void	ft_demo(t_list *cmds, t_list *env)
{
	pid_t	pid;
	t_list	*cmds_cpy;
	int32_t	fds[2];
	t_cmd 	*cmd;

	cmds_cpy = cmds;
	while (cmds_cpy)
	{
		cmd = cmds->content;
		if (!ft_pipe(fds))
		{
			ft_error(-1, "shell", NULL);
			return ;
		}
		if (!ft_fork(&pid))
		{
			ft_error(-1, "shell", NULL);
			return ;
		}
		if (pid == 0)
			ft_child(cmds_cpy->content, fds, env);
		ft_parent(cmds_cpy, fds, env, pid);
		cmds_cpy = cmds_cpy->next;
	}
}

/*

	t_cmd	*cmd = cmds->content;
	int32_t fd = ft_openfile("lol", true);

	if (!ft_pipe(fds))
	{
        ft_error(-1, "shell", NULL);
		return ;
	}
	if (!ft_fork(&pid))
	{
        ft_error(-1, "shell", NULL);
		return ;
	}
	if (pid == 0)
		ft_child(cmd, fds, env);
	else
	{
		char buf[256] = {0}; 

		close(fds[WRITE]);
		for (int n = 0; (n = read(fds[READ], buf, sizeof(buf))) > 0;)
     		write(fd, buf, n); 
		if (waitpid(pid, &status, 0) == -1) 
        	ft_error(-1, "shell", NULL);
		close(fds[READ]);
	}
	close(fd);
}
*/

/**
 * The behaviour loop for the shell itself.
 * 
 * @param env The environment variable.
 */
void	ft_shell(t_list *env)
{
	t_list	*cmds;
	char	*line; 	// Current input line

	while (true)
	{
		line = readline(TITLE); // TODO: CTRL-'\' FUCKS!
		if ((!line) || ft_strncmp(line, "exit", 4) == 0)
		{
			printf("exit\n");
			return ; // Exit shell
		}
		cmds = ft_lexer(line, env);
		ft_demo(cmds, env);
		ft_lstclear(&cmds, &free);
		add_history(line);
		free (line);
	}
}

/*



		t_var	*DEBUG; // DEBUG shit

		//////////////////////////////////////////
		else if ((DEBUG = ft_env_get(env, line)))
		{
			printf("ENV: %s : %s\n", DEBUG->key, DEBUG->value);
			add_history(line);
		}
		//////////////////////////////////////////

*/

/*

	int32_t fd = ft_openfile("lol", true);

	// Basically fd is now the new STDOUT;
	dup2(fd, STDOUT_FILENO); // Re-driect output
	{
		write(STDOUT_FILENO, line, ft_strlen(line));
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, line, ft_strlen(line));
	}
	dup2(g_shell.stdout_fd, STDOUT_FILENO); // Restore out
	printf("ERRNO: %d\n", errno);
	close(fd);

*/

/*

	pid_t	pid;
	int32_t	status;

	if (!ft_fork(&pid))
		return ;
	if (pid == 0) // Child
	{
		char	*args[] = {"LOL", NULL};
		execv("LOL", args);
		ft_error(ENOENT, "LOL", "command not found\n");
		if (errno == ENOENT)
			exit (EXIT_NOTFOUND);
		exit (EXIT_FAILURE);
	}
	if (waitpid(pid, &status, 0) == -1) 
        exit(EXIT_FAILURE);
    if (WIFEXITED(status)) // Did it exit normally ?
        printf("Exit status was %d : ERR: %d\n", WEXITSTATUS(status), errno);

*/

// For every command, we basically make a fork.
// That fork does it shit and then returns to the parent
// Depending on the exit code we then write a corresponding
// error and continue.

// Additionally we need to then handle pipes by basically 
// creating single pipe, child direct its output to the 
// write part of the pipe, while parent reads from the pipe
// parent then redirects the read to wherever the command wanted
// to send the output to, say STDOUT or the file.

/*

	t_cmd			*cmd;
	t_list			*tbl_cpy;
	const t_list	*tbl = ft_lexer(line, env);

	tbl_cpy = tbl;
	while (tbl)
	{
		cmd = tbl_cpy->content;
		
		if (!ft_getexec(cmd->cmd_name, env))
		{
			printf("%s: command not found", cmd->cmd_name);
			continue ;
		}
		
	}
	ft_lstclear(&tbl, &ft_delete_tbl);

*/