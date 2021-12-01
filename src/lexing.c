/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexing.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/01 20:13:32 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/01 21:04:22 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

int32_t	lexer(char *s, char **envp)
{
	t_cmd	*table;
	int		i;
	int		j;
	int		temp;
	int		count;

	i = 0;
	temp = 0;
	table = (t_cmd *)malloc(sizeof(t_cmd));
	while (s[i] != ' ')
		i++;
	table->cmd_name = ft_getexec(ft_substr(s, 0, i), envp);
	if (!table->cmd_name)
		return (1);
	i++;
	j = i;
	while (s[j++])
		if (s[j] == ' ' && s[j - 1] != ' ')
			temp++;
	table->args = (char **)malloc(sizeof(char *) * temp + 1);
	count = 0;
	temp = i;
	while (s[i])
	{
		if (s[i + 1] == ' ' || s[i + 1] == 0)
		{
			table->args[count] = ft_substr(s, temp, (i + 1) - temp);
			temp = i + 2;
			count++;
			i++;
		}
		i++;
	}
	printf("cmd: %s\n", table->cmd_name);
	for (int x = 0; x < count; x++)
		printf("args: %s\n", table->args[x]);
	return (0);
}
