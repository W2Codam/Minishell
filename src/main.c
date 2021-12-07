/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 13:23:11 by lde-la-h      #+#    #+#                 */
/*   Updated: 2021/12/07 14:11:10 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

void	printfunc(t_cmd *nt)
{
	printf("cmd: %s\n", nt->cmd_name);
	for (int x = 0; nt->args[x]; x++)
		printf("arg: %s\n", nt->args[x]);
	if (nt->in.path)
		printf("pathin: %s\n", nt->in.path);
	else
		printf("pathin: STDIN\n");
	if (nt->out.path)
		printf("pathout: %s\n", nt->out.path);
	else
		printf("pathotu: STDOUT\n");
	if (nt->next)
		printfunc(nt->next);
}

int32_t	handlecmd(char *s, char **envp)
{
	t_cmd	*cmdtable = lexer(s, envp);

	if (cmdtable)
		printfunc(cmdtable);
	else
		printf("error\n");
	return (0);
}

int32_t	main(int32_t argc, char **argv, char **envp)
{
	char				*s;

	rl_catch_signals = false;
	SHUTFUCK(argc);
	SHUTFUCK(argv);
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
	while (true)
	{
		s = readline(TITLE);
		if (s == NULL || ft_strnstr(s, "exit", 4))
			break ;
		if (*s == 0)
			continue ;
		if (!handlecmd(s, envp))
			add_history(s);
		free(s);
	}
	exit(EXIT_SUCCESS);
}
