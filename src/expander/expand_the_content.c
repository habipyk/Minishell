/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_the_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbozan <sbozan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:33:23 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 23:33:39 by sbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	c_index(char *content, int *i, int flag)
{
	while (content[*i] && content[*i] != '$' && content[*i] != D_QUOTES)
	{
		if (flag == 1 && content[*i] == S_QUOTES)
			break ;
		*i += 1;
	}
	return (*i);
}

int	null_check_substr(char *substr, char *joinedstr)
{
	if (!substr)
	{
		(void)joinedstr;
		return (1);
	}
	return (0);
}

char	*straight_expand(t_prime *data, char *c, int *end, int *env)
{
	int		i;
	int		start;
	char	*joinedstr;
	char	*sub;

	joinedstr = ft_strdup("");
	i = *end;
	while (c[i] && !is_quotes(c[i]))
	{
		start = i;
		if (c[i] != '$')
			sub = ft_substr(c, start, c_index(c, &i, 1) - start);
		else
		{
			sub = dollar_analysis(c, &i, data, env);
			if (sub && !*sub && !*end && !c[i] &&!is_quotes(c[*end + 1]))
				*env = -1;
			if (null_check_substr(sub, joinedstr))
				break ;
		}
		joinedstr = ft_strjoin(joinedstr, sub);
		free(sub);
	}
	*end = i;
	return (joinedstr);
}

char	*d_quotes_expand(t_prime *data, char *content, int *end, int *env)
{
	int		start;
	int		i;
	char	*substr;
	char	*joinedstr;

	joinedstr = ft_strdup("");
	i = *end + 1;
	while (content[i] && content[i] != D_QUOTES)
	{
		start = i;
		if (content[i] != '$')
			substr = ft_substr(content, start, c_index(content, &i, 0) - start);
		else
		{
			substr = dollar_analysis(content, &i, data, env);
			if (null_check_substr(substr, joinedstr))
				break ;
		}
		joinedstr = ft_strjoin(joinedstr, substr);
		free(substr);
	}
	*end = i;
	if (content[i] != '\0')
		*end = i + 1;
	return (joinedstr);
}

char	*quotes_trim(char *content, int *end, char quotes)
{
	int		i;
	int		start;
	char	*substr;

	i = *end + 1;
	start = i;
	while (content[i] && content[i] != quotes)
		i++;
	substr = ft_substr(content, start, i - start);
	*end = i;
	if (content[i])
		*end = i + 1;
	return (substr);
}
