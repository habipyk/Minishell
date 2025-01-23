/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_init_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:33:13 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:55:29 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_expander	*expander_listnew(char *content, t_lexer *lexer, int env)
{
	t_expander	*new;

	new = (t_expander *)malloc(sizeof(t_expander));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = lexer->type;
	new->env = env;
	new->ex_content = NULL;
	if (env == -1)
		new->ex_content = ft_strdup(lexer->content);
	new->next = NULL;
	return (new);
}

t_expander	*expander_lstlast(t_expander *lst)
{
	t_expander	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	expander_lstadd_back(t_expander **lst, t_expander *new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		expander_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

void	expander_add_node(t_expander **expand, char *str, t_lexer *lex, int env)
{
	if (!str)
		free_expander(expand);
	else
		expander_lstadd_back(expand, expander_listnew(str, lex, env));
}
