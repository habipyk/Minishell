/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wspace_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbozan <sbozan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:02:21 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 23:34:32 by sbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_quotes(char c)
{
	return (c == D_QUOTES || c == S_QUOTES);
}

int	strchr_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (is_quotes(str[i]))
			return (1);
	}
	return (0);
}

int	is_wspace(char c)
{
	return (c == 9 || c == 10 || c == 13 || c == 32);
}

int	strchr_wspace(char *str)
{
	if (ft_strchr(str, 9))
		return (9);
	if (ft_strchr(str, 10))
		return (10);
	if (ft_strchr(str, 13))
		return (13);
	if (ft_strchr(str, 32))
		return (32);
	return (0);
}
