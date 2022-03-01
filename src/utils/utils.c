/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:00:58 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/03/01 23:01:56 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exitout(char *s)
{
	if (s == NULL)
		ft_putendl("\x1b[A\x1b[19Cexit");
	else
	{
		ft_putendl("exit");
		free(s);
	}
}

void	ft_cleanup(char **out)
{
	t_u32	i;

	i = 0;
	if (!out)
		return ;
	if (!out[0] && out[1])
		i = 1;
	while (out[i] != NULL)
		free(out[i++]);
	free(out);
	return ;
}

void	ft_cleantbl(t_list **cmds)
{
	t_cmd	*temp;
	t_list	*cpy;

	cpy = (*cmds);
	while (cpy)
	{
		temp = cpy->content;
		free(temp->cmd_name);
		ft_cleanup(temp->argv);
		if (temp->in.path)
			free(temp->in.path);
		if (temp->out.path)
			free(temp->out.path);
		free(temp);
		free(cpy);
		cpy = cpy->next;
	}
}
