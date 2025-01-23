/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out_fd_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:54:29 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	directory_check(char *filename, t_prime *data, t_parser *parser)
{
	struct stat	st;
	char		*path;
	int			i;
	int			*fd;

	fd = &parser->outfile;
	if (!stat(filename, &st) && S_ISDIR(st.st_mode))
		file_error(filename, "is a directory!", fd, data);
	else if (stat(filename, &st) != 0)
	{
		i = ft_strlen(filename);
		while (--i >= 0 && filename[i] && filename[i] != '/')
			;
		path = ft_substr(filename, 0, i + 1);
		if (stat(path, &st) != 0 && ft_strchr(path, '/'))
			file_error(filename, "No such file or directory", fd, data);
		else if (stat(path, &st) == 0)
			if (S_ISDIR(st.st_mode))
				if (!ownstrcmp(path, "/") || !ownstrcmp(path, "/Users/"))
					file_error(filename, "Permission denied", fd, data);
		free(path);
	}
}

int	outfile_init(t_expander *expander, t_prime *data, t_parser *parser)
{
	char	*filename;
	int		*fd;

	fd = &parser->outfile;
	filename = expander->next->content;
	if (*expander->next->content == '\\')
		filename = expander->next->content + 1;
	directory_check(filename, data, parser);
	if (*fd != 2)
	{
		if (expander->type == SIGN_SOR)
			*fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
		else if (expander->type == SIGN_DOR)
			*fd = open(filename, O_CREAT | O_RDWR | O_APPEND, 0777);
	}
	return (*fd);
}

int	infile_init(t_expander *expander, t_parser *parser, t_prime *data)
{
	struct stat	st;
	char		*fn;
	int			*fd;

	(void)data;
	fd = &parser->infile;
	if (expander->type == SIGN_SIR)
	{
		fn = expander->next->content;
		if (expander->ex_content)
			fn = expander->ex_content;
		else if (*expander->next->content == '\\')
			fn = expander->next->content + 1;
		if (stat(expander->next->content, &st) != 0)
			file_error(fn, "No such file or directory", fd, data);
		else
			*fd = open(fn, O_RDONLY, 0777);
	}
	if (expander->type == HEREDOC)
		*fd = -2;
	return (*fd);
}
