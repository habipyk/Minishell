/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:01:24 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	n_control(char *str)
{
	int	i;

	i = -1;
	if (str[++i] == '-')
	{
		if (str[i + 1] != 'n')
			return (0);
		while (str[++i])
			if (str[i] != 'n')
				return (0);
	}
	else
		return (0);
	return (1);
}

void	run_echo(t_prime *data, t_parser *parser)
{
	char	**path;
	int		nl;

	data->exit_code = 0;
	nl = 0;
	path = &parser->parameters[1];
	while (*path && n_control(*path) == 1)
	{
		nl = 1;
		path++;
	}
	while (*path)
	{
		if (*path)
			write(parser->outfile, *path, ft_strlen(*path));
		if (*(++path))
			write(parser->outfile, " ", 1);
	}
	if (!nl)
		write(parser->outfile, "\n", 1);
}
