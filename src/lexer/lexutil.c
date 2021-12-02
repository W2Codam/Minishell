/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexutil.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pvan-dij <pvan-dij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/02 20:24:16 by pvan-dij      #+#    #+#                 */
/*   Updated: 2021/12/02 20:27:42 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mongolshell.h"

void	cmd_lstadd_back(t_cmd **lst, t_cmd *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
		cmd_lstlast(*lst)->next = new;
}

t_cmd	*cmd_lstlast(t_cmd *lst)
{
	while (lst)
	{
		if (!lst->next)
			break ;
		lst = lst->next;
	}
	return (lst);
}
