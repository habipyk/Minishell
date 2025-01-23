/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:02:42 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_pwd(t_prime *data, t_parser *parser)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(parser->outfile, pwd, ft_strlen(pwd));
	write(parser->outfile, "\n", 1);
	data->exit_code = 0;
}
