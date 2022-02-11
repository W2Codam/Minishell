/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stringexpand.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 13:38:16 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/02/11 17:33:13 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expandenv(char *cmd, t_list *envp)
{
	t_var	*temp;
	char	*out;
	bool	found;

	found = false;
	while (envp && found == false)
	{
		temp = envp->content;
		if (!ft_strncmp(cmd + 1, temp->key, ft_strlen(cmd + 1)))
			found = true;
		envp = envp->next;
	}
	if (found == false || temp->unset == true)
		return ("");
	return (temp->value);
}

void	expandshit(t_qoute *cmd, char *s, t_list *envp)
{
	const char	qt[2] = {'\"', '\''};
	int			state;
	char		*save;

	save = s;
	while (*s)
	{
		
	}
	
}

t_qoute	*ft_stringexpand(char *in, t_list *envp)
{
	t_qoute	*out;
	int		i;

	out = splitting(in);
	i = 0;
	while (out[i].arg != NULL)
	{
		if (ft_strchr(out[i].arg, '\'') || ft_strchr(out[i].arg, '\"') \
			|| ft_strchr(out[i].arg, '$'))
			expandshit(&out[i], out[i].arg, envp);
		else
			out[i].qouted = false;
		i++;
	}
	for (int i = 0; out[i].arg; i++)
		printf("%s\n", out[i].arg);
	exit(0);
	return (out);
}
