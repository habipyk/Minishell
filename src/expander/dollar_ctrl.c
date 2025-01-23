/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbozan <sbozan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:40:45 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 23:33:39 by sbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*check_env(t_prime *data, char *substr, int	*env)
{
	t_env_l	*iter;
	char	*str;

	iter = data->env_l;
	str = NULL;
	while (iter)
	{
		if (!ownstrcmp(iter->name, substr))
		{
			str = ft_strdup(iter->content);
			*env = 1;
			break ;
		}
		iter = iter->next;
	}
	if (*env != 1)
		str = ft_strdup("");
	free (substr);
	return (str);
}

char	*dollar_expand(char *content, int *end, t_prime *data, int *env)
{
	char	*substr;
	int		start;
	int		i;

	i = *end;
	start = i;
	while (content[i] && (ft_isalpha(content[i])
			|| ft_isdigit(content[i]) || content[i] == '_'))
		i++;
	substr = ft_substr(content, start, i - start);
	substr = check_env(data, substr, env);
	*end = i;
	return (substr);
}

char	*special_expand(char c, t_prime *data, int *i)
{
	char	*substr;

	substr = NULL;
	*i += 1;
	if (c == '0')
		substr = ft_substr("minishell", 0, 9);
	if (c == '?')
	{
		if (g_signal == 1)
		{
			substr = ft_strdup("1");
			g_signal = 0;
		}
		else
			substr = ft_itoa(data->exit_code);
	}
	return (substr);
}

char	*dollar_analysis(char *str, int *end, t_prime *data, int *env)
{
	int		i;
	int		start;
	char	*substr;

	i = *end;
	start = i + 1;
	substr = NULL;
	if (ret_null(str[++i]))
		substr = ft_strdup("");
	else if (put_directly(str[i], &i))
		substr = ft_substr(str, start - 1, i - *end);
	else if (special_chars(str[i]))
		substr = special_expand(str[i], data, &i);
	else if (str[i] == '$')
		substr = ft_strdup("$");
	else if (is_quotes(str[i]))
		substr = quotes_trim(str, &i, str[i]);
	else
		substr = dollar_expand(str, &i, data, env);
	if (ret_null(str[i]) || special_chars(str[i]))
		i++;
	*end = i;
	return (substr);
}
