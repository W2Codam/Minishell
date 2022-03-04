/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lde-la-h <lde-la-h@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:00:58 by lde-la-h      #+#    #+#                 */
/*   Updated: 2022/03/04 18:09:21 by pvan-dij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exitout(char *s)
{
	if (s == NULL)
	{
		ft_putendl("\x1b[A\x1b[19Cexit");
		return (0);
	}
	else
	{
		ft_putendl("exit");
		free(s);
	}
	return (0);
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

/**
 * Cleans up all the malloced elements of the command table
 * 
 * @param cmds The command table
 */
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
		if (temp->in.path || temp->in.fd > 1)
		{
			close(temp->in.fd);
			free(temp->in.path);
		}
		if (temp->out.path || temp->out.fd > 1)
		{
			close(temp->out.fd);
			free(temp->out.path);
		}
		free(temp);
		free(cpy);
		cpy = cpy->next;
	}
	(*cmds) = NULL;
}

//fucking add this to libft
bool	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	if (s1[i] != s2[i])
		return (false);
	return (true);
}
