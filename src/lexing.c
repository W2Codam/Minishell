/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexing.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 20:13:32 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/02 14:29:42 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

int32_t	lexonecmd(char *s, char **envp, t_cmd *table)
{
	int		i;
	int		j;
	int		temp;
	int		count;
	t_cmd	newtable;

	i = 0;
	temp = 0;
	while (s[i] != ' ')
		i++;
	newtable.cmd_name = ft_getexec(ft_substr(s, 0, i), envp);
	if (!newtable.cmd_name)
		return (1);
	i++;
	j = i;
	while (s[j++])
		if (s[j] == ' ' && s[j - 1] != ' ')
			temp++;
	newtable.args = (char **)malloc(sizeof(char *) * temp + 1);
	count = 0;
	temp = i;
	while (s[i])
	{
		if (s[i + 1] == ' ' || s[i + 1] == 0)
		{
			newtable.args[count] = ft_substr(s, temp, (i + 1) - temp);
			temp = i + 2;
			count++;
			i++;
		}
		i++;
	}
	printf("cmd: %s\n", newtable.cmd_name);
	for (int x = 0; x < count; x++)
	{
		printf("args: %s\n", newtable.args[x]);
		free(newtable.args[x]);
	}
	newtable.next = NULL;
	table = &newtable;
	return (0);
}

int32_t	lexer(char *s, char **envp)
{
	t_cmd	*table;
	int		i;
	int		count;
	int		j;
	int		k;

	count = 1;
	i = 0;
	while (s[i++])
		if (s[i] == '|')
			count++;
	table = (t_cmd *)malloc(sizeof(t_cmd));
	i = 0;
	j = 0;
	k = 0;
	while (i < count)
	{
		while (s[j] != '|' && s[j])
			j++;
		lexonecmd(ft_substr(s, k, j - k), envp, table);
		table = table->next;
		k = j;
		while (s[k] == ' ' || s[k] == '|')
			k++;
		j++;
		i++;
	}
	return (0);
}

//allocate for amount of cmd
//lex command by command, substr between start and pipe, pipes, and pipe and \0
