/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexing.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 20:13:32 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/02 20:37:55 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

void printfunc(t_cmd *nt, int count)
{
	printf("cmd: %s\n", nt->cmd_name);
	for (int x = 0; x < count; x++)
		printf("args: %s\n", nt->args[x]);
	if (nt->in.path)
		printf("pathin: %s\n", nt->in.path);
	else
		printf("pathin: STDIN\n");
	if (nt->out.path)
		printf("pathout: %s\n", nt->out.path);
	else
		printf("pathotu: STDOUT\n");
}

/**
 * Lexes one command. Returns 0 on succes.
 * Doesn't handle qoutes yet.
 * 
 * @param s 
 * @param envp 
 * @param table 
 * @return int32_t 
 */
t_cmd	*lexonecmd(char *s, char **envp)
{
	int		i;
	int		j;
	int		temp;
	int		count;
	t_cmd	*newtable;

	i = 0;
	temp = 0;
	newtable = (t_cmd *)malloc(sizeof(t_cmd));
	s = find_inout(s, newtable);
	while (s[i] != ' ')
		i++;
	newtable->cmd_name = ft_getexec(ft_substr(s, 0, i), envp);
	if (!newtable->cmd_name)
		return (NULL);
	i++;
	j = i;
	while (s[j++])
		if (s[j] == ' ' && s[j - 1] != ' ')
			temp++;
	newtable->args = (char **)malloc(sizeof(char *) * temp + 1);
	count = 0;
	temp = i;
	while (s[i])
	{
		if (s[i + 1] == ' ' || s[i + 1] == 0)
		{
			newtable->args[count] = ft_substr(s, temp, (i + 1) - temp);
			temp = i + 2;
			count++;
			i++;
		}
		i++;
	}
	printfunc(newtable, count);
	newtable->next = NULL;
	return (newtable);
}

/**
 * Finds the amount of commands and sends them to lexonecmd.
 * Returns the populated cmdtable.
 * 
 * @param s 
 * @param envp 
 * @return t_cmd *
 */
t_cmd	*lexer(char *s, char **envp)
{
	t_cmd	*temp;
	t_cmd	*table;
	int		j;
	int		k;

	j = 1;
	k = 0;
	table = NULL;
	while (strchr(s + j - 1, '|'))
	{	
		temp = (t_cmd *)malloc(sizeof(t_cmd));
		while (s[j] != '|' && s[j])
			j++;
		temp = lexonecmd(ft_substr(s, k, j - k), envp);
		if (!temp)
			return (NULL);
		cmd_lstadd_back(&table, temp);
		k = j;
		while (s[k] == ' ' || s[k] == '|')
			k++;
		j++;
	}		
	printf("%s\n", table->cmd_name);
	return (table);
}

// TODO: norm everything, possible rewrites, remove printfunc when needed