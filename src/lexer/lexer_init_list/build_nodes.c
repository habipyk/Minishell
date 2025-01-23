/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbozan <sbozan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:40:50 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 23:35:09 by sbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	create_nodes(t_prime *data, t_list *lex_mlist)
{
	t_list	*temp;

	temp = lex_mlist;
	while (temp)
	{
		if (!check_metachar(temp->content) || strchr_quotes(temp->content))
			lexer_add_node(&data->lexer, temp->content, 0);
		else
			lexer_add_node(&data->lexer, temp->content, \
				is_metachar(*(char *)temp->content));
		lex_mlist = temp;
		temp = temp->next;
		free(lex_mlist->content);
		free(lex_mlist);
	}
}
