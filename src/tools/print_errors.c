/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:08:00 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	synerr_print(t_prime *data, char *str, int f)
{
	if (f == 1)
		write(2, "minishell: ", 11);
	else
		write(2, "minishell: syntax error near unexpected token ", 51);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	data->exit_code = 258;
	return (-1);
}

void	file_error(char *filename, char *str, int *fd, t_prime *data)
{
	write(2, "minishell: ", 10);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	*fd = 2;
	data->exit_code = 1;
}

void	print_error(t_prime *data, char *str)
{
	write(2, "minishell: ", 10);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	data->exit_code = 258;
	return ;
}

int	command_error(char *arg, char *cmd, char *str, t_prime *data)
{
	write(2, "minishell: ", 10);
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	data->exit_code = 1;
	data->parser->outfile = 1;
	return (1);
}
