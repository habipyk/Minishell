/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:02:23 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_export(t_prime *data, t_parser *parser)
{
	int		array_len;
	char	**temp_path;

	data->exit_code = 0;
	array_len = parameters_count(parser->parameters);
	if (array_len > 1)
	{
		temp_path = parser->parameters;
		while (*(++temp_path))
			double_export_arg(data, *temp_path);
	}
	else
		single_export_arg(data, parser);
}

void	single_export_arg(t_prime *data, t_parser *parser)
{
	t_env_l	*env;

	env = data->env_l;
	while (env)
	{
		write(parser->outfile, "declare -x ", 11);
		write(parser->outfile, env->name, ft_strlen(env->name));
		if (!env->content)
		{
			write(parser->outfile, "\n", 1);
			env = env->next;
			continue ;
		}
		write(parser->outfile, "=\"", 2);
		write(parser->outfile, env->content, ft_strlen(env->content));
		write(parser->outfile, "\"\n", 2);
		env = env->next;
	}
}

int	change_env(t_prime *data, char *envname, char *arg, int is_equal)
{
	t_env_l	*env;

	env = data->env_l;
	while (env)
	{
		if (!ownstrcmp(envname, env->name))
		{
			if (is_equal)
				update_env(data, envname, arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	double_export_arg(t_prime *data, char *env_cmd)
{
	char	*arg;
	int		is_equal;
	t_env_l	*env;
	char	*temp_envname;

	if (!env_arg_control(data, env_cmd))
	{
		data->exit_code = 1;
		return ;
	}
	temp_envname = get_env_name(env_cmd);
	arg = env_cmd + ft_strlen(temp_envname);
	is_equal = 0;
	if (*arg == '=')
		is_equal |= 1;
	if (change_env(data, temp_envname, ++arg, is_equal))
	{
		free(temp_envname);
		return ;
	}
	env = data->env_l;
	add_newenv(data, env_cmd);
	if (!is_equal)
		update_env(data, env_cmd, NULL);
	free(temp_envname);
}
