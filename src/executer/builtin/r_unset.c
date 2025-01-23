/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:03:07 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	run_unset(t_prime *data)
{
	char	**temp_name;
	int		array_len;

	data->exit_code = 0;
	array_len = parameters_count(data->parser->parameters);
	if (array_len > 1)
	{
		temp_name = data->parser->parameters;
		while (*(++temp_name))
		{
			if (!env_arg_control(data, *temp_name))
			{
				command_error(0, "unset", "not a valid identifier", data);
				continue ;
			}
			else
				delete_env(data, *temp_name);
		}
	}
}

void	delete_env(t_prime *data, char *name)
{
	t_env_l	*env;
	t_env_l	*temp_env;

	env = data->env_l;
	while (env)
	{
		if (!ownstrcmp(env->name, name))
		{
			if (env->content)
				free(env->content);
			free(env->name);
			if (data->env_l == env)
				data->env_l = data->env_l->next;
			else
				temp_env->next = env->next;
			free(env);
			break ;
		}
		temp_env = env;
		env = env->next;
	}
}
