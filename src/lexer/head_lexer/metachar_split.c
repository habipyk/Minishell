/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metachar_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbozan <sbozan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:28:49 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 23:35:09 by sbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	metachar_split3(char *content, int *end)
{
	char	quotes;

	while (content[*end] && !is_metachar(content[*end]))
	{
		if (is_quotes(content[*end]))
		{
			quotes = content[*end];
			*end += 1;
			while (content[*end] && content[*end] != quotes)
				*end += 1;
		}
		*end += 1;
	}
}

void	metachar_split2(char *content, t_list **lex_mlist)
{
	int		end;
	int		start;

	end = 0;
	while (content[end])
	{
		start = end;
		if (is_metachar(content[start]))
			while (content[end] && content[end] == content[start])
				end++;
		else
			metachar_split3(content, &end);
		ft_lstadd_back(lex_mlist, \
			ft_lstnew(ft_substr(content, start, end - start)));
	}
	free(content);
}

t_list	*metachar_split(t_list *lex_slist)
{
	t_list	*temp;
	t_list	*lex_mlist;

	lex_mlist = NULL;
	temp = lex_slist;
	while (temp)
	{
		if (!check_metachar(temp->content))
			ft_lstadd_back(&lex_mlist, ft_lstnew(temp->content));
		else
			metachar_split2(temp->content, &lex_mlist);
		lex_slist = temp;
		temp = temp->next;
		free(lex_slist);
	}
	return (lex_mlist);
}
