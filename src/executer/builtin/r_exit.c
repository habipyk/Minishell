/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:02:01 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_all_numeric(char *text)
{
	while (text && *text)
	{
		if (*text == '-' || *text == '+')
			text++;
		if (!ft_isdigit(*text))
			return (0);
		text++;
	}
	return (1);
}

void	run_exit(t_prime *data, t_parser *parser)
{
	int	array_len;

	data->exit_code = 0;
	if (data->cmd_count == 1)
		printf("exit\n");
	array_len = parameters_count(&parser->parameters[1]);
	if (parser->parameters[1] && is_all_numeric(parser->parameters[1]))
	{
		data->exit_code = ft_atoi(parser->parameters[1]) % 256;
		if (parser->parameters[1][0] == '-')
			data->exit_code = 256 - (-1 * data->exit_code);
		if (array_len > 1)
		{
			command_error(0, "exit", "too many arguments", data);
			return ;
		}
	}
	else if (parser->parameters[1] && !is_all_numeric(parser->parameters[1]))
	{
		command_error(parser->parameters[1], "exit", \
			"numeric argument required", data);
		data->exit_code = 255;
	}
	exit(data->exit_code);
}
