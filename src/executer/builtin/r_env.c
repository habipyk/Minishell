/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:01:44 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_env(t_prime *data, t_parser *parser)
{
	t_env_l	*temp_env;

	if (!search_path(data->env_l, "PATH"))
	{
		command_error(0, "env", "No such file or directory", data);
		data->exit_code = 127;
		return ;
	}
	temp_env = data->env_l;
	while (temp_env)
	{
		if (temp_env->content)
		{
			write(parser->outfile, temp_env->name,
				ft_strlen(temp_env->name));
			write(parser->outfile, "=", 1);
			write(parser->outfile, temp_env->content,
				ft_strlen(temp_env->content));
			write(parser->outfile, "\n", 1);
		}
		temp_env = temp_env->next;
	}
	data->exit_code = 0;
}
