/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:48:03 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	open_pipes(t_prime *data)
{
	int	**fd;
	int	i;

	if (data->cmd_count > 1)
	{
		fd = (int **)malloc(sizeof(int *) * (data->cmd_count - 1));
		i = -1;
		while (++i < data->cmd_count - 1)
			fd[i] = malloc(sizeof(int) * 2);
		data->fd = fd;
		i = -1;
		while (++i < data->cmd_count - 1)
			pipe(data->fd[i]);
	}
}

void	wait_all(t_prime *data, int builtin)
{
	t_parser	*parser;
	int			status;

	parser = data->parser;
	while (parser && builtin <= 1)
	{
		waitpid(parser->pid, &status, 0);
		data->exit_code = status / 256;
		if (parser->outfile == 2 || parser->infile == 2)
			data->exit_code = 1;
		parser = parser->next;
	}
	g_signal = 0;
}

void	fd_closer(t_prime *data)
{
	int	i;

	i = -1;
	while (++i < data->cmd_count - 1)
	{
		if (data->fd[i][1])
			close(data->fd[i][1]);
		if (data->fd[i][0])
			close(data->fd[i][0]);
	}
}
