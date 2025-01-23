/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:52:13 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*temp;

	if (!lexer)
		return ;
	while (*lexer)
	{
		temp = (*lexer)->next;
		free((*lexer)->content);
		*lexer = free_null(*lexer);
		*lexer = temp;
	}
}

void	free_expander(t_expander **expander)
{
	t_expander	*temp;

	if (!expander)
		return ;
	while (*expander)
	{
		temp = (*expander)->next;
		(*expander)->content = free_null((*expander)->content);
		if ((*expander)->ex_content)
			free((*expander)->ex_content);
		*expander = free_null(*expander);
		*expander = temp;
	}
}

void	free_file(t_parser **parser)
{
	t_files	*temp;

	while ((*parser)->file)
	{
		temp = (*parser)->file->next;
		free ((*parser)->file->filename);
		free ((*parser)->file);
		(*parser)->file = temp;
	}
	(*parser)->file = free_null((*parser)->file);
}

void	free_parser(t_parser **parser)
{
	t_parser	*temp;
	int			i;

	if (!parser)
		return ;
	while (*parser)
	{
		temp = (*parser)->next;
		(*parser)->command = free_null((*parser)->command);
		i = -1;
		while ((*parser)->parameters && (*parser)->parameters[++i])
			free((*parser)->parameters[i]);
		free ((*parser)->parameters);
		if ((*parser)->heredoc)
			(*parser)->heredoc = free_null((*parser)->heredoc);
		if ((*parser)->file)
			free_file(parser);
		*parser = free_null(*parser);
		*parser = temp;
	}
}

void	free_prime(t_prime *data)
{
	int	i;

	free_lexer(&data->lexer);
	free_expander(&data->expander);
	free_parser(&data->parser);
	data->line = free_null(data->line);
	data->line = NULL;
	i = 0;
	while (i < data->cmd_count - 1)
	{
		if (data->fd && data->fd[i])
			free(data->fd[i]);
		i++;
	}
	if (data->fd)
		free(data->fd);
}
