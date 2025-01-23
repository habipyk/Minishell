/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:48:06 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_execve(t_prime *data, t_parser *parser, int i, int builtin)
{
	char	**env_list;
	char	*command;

	command = NULL;
	env_list = NULL;
	dup_stdio(data, parser, i);
	if (builtin > 2 || builtin < 0)
	{
		run_builtin(data, parser, builtin, i);
		exit (0);
	}
	env_list = get_env_cpy(data);
	command = get_command(data, parser);
	if (!search_path(data->env_l, "PATH") && builtin == 0)
	{
		if (access(parser->command, F_OK))
		{
			command_error(0, parser->command, \
				"No such file or directory", data);
			exit (127);
		}
	}
	execve(command, parser->parameters, env_list);
	command_error(0, parser->command, "command not found!", data);
	exit(127);
}

void	run_builtin(t_prime *data, t_parser *parser, int built_type, int i)
{
	(void)i;
	if (built_type == EKHO)
		run_echo(data, parser);
	else if (built_type == CD)
		run_cd(data);
	else if (built_type == PWD)
		run_pwd(data, parser);
	else if (built_type == EXPORT)
		run_export(data, parser);
	else if (built_type == UNSET)
		run_unset(data);
	else if (built_type == ENV)
		run_env(data, parser);
	else if (built_type == EXIT)
		run_exit(data, parser);
}
