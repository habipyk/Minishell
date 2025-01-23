/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbozan <sbozan@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:37:06 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 23:35:09 by sbozan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_metachar(char c)
{
	if (c == PIPE)
		return (SIGN_PIPE);
	else if (c == SOR)
		return (SIGN_SOR);
	else if (c == SIR)
		return (SIGN_SIR);
	else
		return (TEXT);
}

int	check_metachar(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (is_metachar(content[i]))
			return (1);
		i++;
	}
	return (0);
}
