/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:04:42 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:55:29 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*buffer(char *nextline, int fd)
{
	int		countread;
	char	*buf;

	buf = malloc(sizeof(char) * (100));
	if (!buf)
		return (0);
	countread = 1;
	while (countread != 0)
	{
		countread = read(fd, buf, 100);
		if (countread == -1)
		{
			nextline = free_null(nextline);
			buf = free_null(buf);
			return (0);
		}
		buf[countread] = '\0';
		nextline = ft_strjoin(nextline, buf);
	}
	buf = free_null(buf);
	return (nextline);
}

char	*get_line(int fd)
{
	char		*outline;

	outline = NULL;
	if (1 <= 0 || fd < 0)
		return (0);
	outline = buffer(outline, fd);
	if (!(outline))
		return (0);
	return (outline);
}
