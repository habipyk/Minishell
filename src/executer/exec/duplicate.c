/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:47:58 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	tempfd_init(t_prime *data, t_parser *parser, int i)
{
	if (data->parser == parser)
		dup2(data->fd[i][1], STDOUT_FILENO);
	else if (!parser->next)
		dup2(data->fd[i - 1][0], STDIN_FILENO);
	else
	{
		dup2(data->fd[i - 1][0], STDIN_FILENO);
		dup2(data->fd[i][1], STDOUT_FILENO);
	}
	fd_closer(data);
}

void	dup_stdio(t_prime *data, t_parser *parser, int i)
{
	int	fd[2];

	signal(SIGINT, interrupt_here_document);
	if (data->cmd_count > 1 && ownstrcmp(parser->command, "exit"))
		tempfd_init(data, parser, i);
	if (parser->infile == -2)
	{
		pipe(fd);
		write(fd[1], parser->heredoc, ft_strlen(parser->heredoc));
		close (fd[1]);
		if (parser->next || ownstrcmp(parser->command, "echo"))
			dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (parser->outfile >= 2)
		dup2(parser->outfile, STDOUT_FILENO);
	if (parser->infile >= 2)
		dup2(parser->infile, STDIN_FILENO);
}
