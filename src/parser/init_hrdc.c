/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hrdc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:49:32 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_read(char *end, int write_fd)
{
	char	*input;
	char	*heredoc;

	heredoc = NULL;
	input = NULL;
	while (1)
	{
		input = readline("> ");
		if (!input || ownstrcmp(input, end) == 0)
		{
			write(write_fd, heredoc, ft_strlen(heredoc));
			heredoc = free_null(heredoc);
			input = free_null(input);
			exit(0);
		}
		heredoc = ft_strjoin(heredoc, input);
		heredoc = ft_strjoin(heredoc, "\n");
		input = free_null(input);
	}
}

void	handle_heredoc_child(int fd[2], t_expander *temp_ex)
{
	close(fd[0]);
	signal(SIGINT, interrupt_here_document);
	heredoc_read(temp_ex->next->content, fd[1]);
}

int	handle_heredoc_parent(int fd[2], t_parser *temp_parser, int pid)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (status == 0)
	{
		if (temp_parser->heredoc)
			free(temp_parser->heredoc);
		temp_parser->heredoc = get_line(fd[0]);
		close(fd[0]);
		if (!temp_parser->heredoc)
			exit(EXIT_FAILURE);
	}
	else if (status != 0)
		return (1);
	return (0);
}

int	handle_heredoc_fork(t_expander *temp_ex, t_parser *temp_parser, int fd[2])
{
	int	pid;
	int	ret;

	g_signal = 2;
	pipe(fd);
	ret = 0;
	pid = fork();
	if (pid == 0)
		handle_heredoc_child(fd, temp_ex);
	else
		ret = handle_heredoc_parent(fd, temp_parser, pid);
	close(fd[1]);
	return (ret);
}

void	heredoc_init(t_prime *data)
{
	t_expander	*temp_ex;
	t_parser	*temp_parser;
	int			fd[2];

	temp_ex = data->expander;
	temp_parser = data->parser;
	while (temp_ex)
	{
		while (temp_ex && temp_ex->type != 1)
		{
			if (temp_ex->type == HEREDOC)
			{
				if (handle_heredoc_fork(temp_ex, temp_parser, fd))
				{
					free_parser(&data->parser);
					return ;
				}
			}
			temp_ex = temp_ex->next;
		}
		if (temp_ex)
			temp_ex = temp_ex->next;
		temp_parser = temp_parser->next;
	}
}
