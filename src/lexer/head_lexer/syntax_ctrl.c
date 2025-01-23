/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:41:08 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	syn_error(t_prime *data, int temp_type, int temp_len)
{
	if (temp_type == -1)
		return (synerr_print(data, "||", 0));
	else if (temp_type == -2 && temp_len == 3)
		return (synerr_print(data, ">", 0));
	else if (temp_type == -2 && temp_len > 3)
		return (synerr_print(data, ">>", 0));
	else if (temp_type == -3 && temp_len == 3)
		return (synerr_print(data, "<", 0));
	else if (temp_type == -3 && temp_len < 5)
		return (synerr_print(data, "<<", 0));
	else if (temp_type == -3 && temp_len > 5)
		return (synerr_print(data, "<<<", 0));
	return (0);
}

int	syntax_check(t_prime *data)
{
	t_lexer	*temp;
	int		flag;
	int		t;

	temp = data->lexer;
	type_init(data);
	flag = 0;
	while (temp)
	{
		t = temp->type;
		if (t == -1 || t == -2 || t == -3)
			return (syn_error(data, t, ft_strlen(temp->content)));
		else if (data->lexer->type == SIGN_PIPE || \
			(temp->next && temp->next->type == SIGN_PIPE && t > 0) || \
			(temp->type == SIGN_PIPE && !temp->next))
			return (synerr_print(data, "|", 0));
		else if ((t >= SIGN_SOR && t <= 5) && (!temp->next || temp->next->type))
			flag = 2;
		temp = temp->next;
	}
	if (flag == 2)
		return (synerr_print(data, "newline", 0));
	return (0);
}
