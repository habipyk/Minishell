/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbozan <sbozan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:26:40 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 23:33:39 by sbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_content(t_prime *data, char *content, int *env)
{
	int		end;
	char	*joinedstr;
	char	*substr;

	joinedstr = ft_strdup("");
	end = 0;
	while (content[end])
	{
		if (content[end] == S_QUOTES)
			substr = quotes_trim(content, &end, S_QUOTES);
		else
		{
			if (content[end] == D_QUOTES)
				substr = d_quotes_expand(data, content, &end, env);
			else
				substr = straight_expand(data, content, &end, env);
			if (null_check_substr(substr, joinedstr))
				break ;
		}
		joinedstr = ft_strjoin(joinedstr, substr);
		free(substr);
	}
	return (joinedstr);
}

char	*put_straight(char *content)
{
	int		start;
	int		end;
	char	*substr;
	char	*joinedstr;

	end = 0;
	substr = NULL;
	joinedstr = ft_strdup("");
	while (content[end])
	{
		start = end;
		if (!is_quotes(content[end]))
		{
			while (content[end] && !is_quotes(content[end]))
				end++;
			substr = ft_substr(content, start, end - start);
		}
		else
			substr = quotes_trim(content, &end, content[end]);
		joinedstr = ft_strjoin(joinedstr, substr);
		free(substr);
	}
	return (joinedstr);
}

void	expander(t_prime *data)
{
	t_lexer	*temp;
	int		env;

	if (!data->lexer)
		return ;
	temp = data->lexer;
	while (temp)
	{
		env = 0;
		if (!ownstrcmp(temp->content, "~"))
		{
			free(temp->content);
			temp->content = ft_strdup("$HOME");
		}
		if (!ft_strchr(temp->content, '$'))
			expander_add_node(&data->expander, put_straight(temp->content),
				temp, env);
		else
			expander_add_node(&data->expander, expand_content(data,
					temp->content, &env), temp, env);
		temp = temp->next;
	}
}
