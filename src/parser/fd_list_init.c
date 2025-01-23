/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_list_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:58:16 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:55:29 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_files	*files_listnew(char *name, int type, int fd)
{
	t_files	*new;

	new = (t_files *)malloc(sizeof(t_files));
	if (!new)
		return (0);
	new->filename = name;
	new->re_type = type;
	new->fd = fd;
	new->next = 0;
	return (new);
}

t_files	*files_lstlast(t_files *lst)
{
	t_files	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	files_lstadd_back(t_files **lst, t_files *new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		files_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

void	files_add_node(t_files **files, char *name, int type, int fd)
{
	files_lstadd_back(files, files_listnew(name, type, fd));
}
