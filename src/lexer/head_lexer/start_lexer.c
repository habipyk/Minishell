/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbozan <sbozan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:37:42 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 23:34:32 by sbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_list	*wspace_split(char *line, int start, int end, int quotes)
{
	t_list	*lex_slist;

	lex_slist = NULL;
	while (line && line[end])
	{
		start = end;
		if (is_wspace(line[end]))
			while (line[end] && is_wspace(line[end]))
				end++;
		else
		{
			while (line[end] && !is_wspace(line[end]))
			{
				quotes = line[end];
				if (is_quotes(line[end]))
					while (line[++end] && line[end] != quotes)
						;
				end++;
			}
			ft_lstadd_back(&lex_slist, ft_lstnew \
				(ft_substr(line, start, end - start)));
		}
	}
	return (lex_slist);
}

int	quotes_check2(char *line, int *i, char q)
{
	int	j;

	j = *i;
	while (line[++j])
	{
		if (line[j] == q)
		{
			*i = j + 1;
			return (1);
		}
	}
	return (0);
}

int	quotes_check(char *line)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (is_quotes(line[i]))
		{
			if (quotes_check2(line, &i, line[i]) == 0)
				return (-1);
		}
		else
			while (line[i] && !is_quotes(line[i]))
				i++;
	}
	return (0);
}

void	lexer(t_prime *data)
{
	t_list	*lex_slist;
	t_list	*lex_mlist;

	if (quotes_check(data->line) == -1)
	{
		write(2, "minishell: incorrect use of quotes!\n", 36);
		data->exit_code = 258;
		return ;
	}
	lex_slist = wspace_split(data->line, 0, 0, 0);
	lex_mlist = metachar_split(lex_slist);
	create_nodes(data, lex_mlist);
	if (syntax_check(data) == -1)
		free_lexer(&data->lexer);
}
