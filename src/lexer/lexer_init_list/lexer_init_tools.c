/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:23:49 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:55:29 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_lexer	*lexer_listnew(char *content, int type)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_lexer	*lexer_lstlast(t_lexer	*lst)
{
	t_lexer	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next != 0)
	{
		temp = temp->next;
	}
	return (temp);
}

void	lexer_lstadd_back(t_lexer	**lst, t_lexer	*new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		lexer_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

void	lexer_add_node(t_lexer **lexer, char *str, int type)
{
	lexer_lstadd_back(lexer, \
		lexer_listnew(ft_strdup(str), type));
}
