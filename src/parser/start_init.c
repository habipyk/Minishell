/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:47:50 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pipe_count(t_prime *data)
{
	t_expander	*temp;
	int			pipe_count;

	temp = data->expander;
	pipe_count = 1;
	while (temp)
	{
		if (temp->type == 1)
			pipe_count++;
		temp = temp->next;
	}
	data->cmd_count = pipe_count;
	return (pipe_count);
}

t_parser	*parser_listnew(void)
{
	t_parser	*new;

	new = (t_parser *)ft_calloc(sizeof(t_parser), 1);
	if (!new)
		return (0);
	new->command = 0;
	new->parameters = 0;
	new->heredoc = 0;
	new->infile = 0;
	new->outfile = 1;
	new->file = 0;
	new->next = 0;
	new->pid = -1;
	return (new);
}

t_parser	*parser_lstlast(t_parser *lst)
{
	t_parser	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	parser_lstadd_back(t_parser **lst, t_parser *new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		parser_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

void	parser_addnode(t_parser **parser, int pipe_count)
{
	while (pipe_count--)
		parser_lstadd_back(parser, parser_listnew());
}
