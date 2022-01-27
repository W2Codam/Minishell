/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envproc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 13:44:26 by pvan-dij      #+#    #+#                 */
/*   Updated: 2022/01/27 13:49:15 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"


void	env_lstaddback(t_cmd **lst, t_cmd *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		env_lstlast(*lst)->next = new;
}

t_env	*env_lstlast(t_cmd *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}

t_env	*processenv(char **envp)
{
	t_env	*main;
	t_env	*temp;
	int		i;

	while (envp[i])
	{
		temp = (t_env *)malloc(sizeof(t_env));
		if (!temp)
			return (NULL);
		temp->env = envp[i];
		temp->next = NULL;
		env_lstaddback(&main, temp);
	}
	return (main);
}
