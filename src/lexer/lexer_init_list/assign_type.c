/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:24:03 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	type_match(t_lexer *temp)
{
	if (temp->type == SIGN_SIR && ft_strlen(temp->content) == 2)
		temp->type = HEREDOC;
	else if (temp->type == SIGN_SOR && ft_strlen(temp->content) == 2)
		temp->type = SIGN_DOR;
	else if (temp->type == SIGN_SIR && ft_strlen(temp->content) > 2)
		temp->type = -3;
	else if (temp->type == SIGN_PIPE && ft_strlen(temp->content) > 1)
		temp->type = -1;
	else if (temp->type == SIGN_SOR && ft_strlen(temp->content) > 2)
		temp->type = -2;
}

void	type_init(t_prime *data)
{
	t_lexer	*temp;

	temp = data->lexer;
	while (temp)
	{
		if (temp->type != 0)
			type_match(temp);
		temp = temp->next;
	}
}
