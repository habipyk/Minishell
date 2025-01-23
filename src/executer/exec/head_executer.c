/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_executer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:48:01 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	executer(t_prime *data, int i)
{
	t_parser	*parser;
	int			builtin;

	if (!data->parser)
		return ;
	open_pipes(data);
	parser = data->parser;
	while (parser && ++i)
	{
		builtin = check_builtin(data, parser);
		if (builtin > 2 && data->cmd_count == 1)
			run_builtin(data, parser, builtin, i - 1);
		else if ((data->cmd_count > 1 || builtin < 2) && parser->command)
		{
			g_signal = 2;
			parser->pid = fork();
			if (!parser->pid)
				run_execve(data, parser, i - 1, builtin);
			builtin = 0;
		}
		parser = parser->next;
	}
	fd_closer(data);
	wait_all(data, builtin);
}
