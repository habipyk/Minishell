/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arg_ctrl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:12:44 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	env_name_control(char *env)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!env || env[i] == ' ' || env[i] == '=')
		return (0);
	if (ft_isalpha(env[i]) || env[i] == '_')
		flag = 1;
	while (env[i] && env[i] != ' ' && env[i] != '=' && flag == 1)
	{
		if ((!ft_isdigit(env[i]) && !ft_isalpha(env[i]) && env[i] != '_')
			|| !flag)
			return (0);
		i++;
	}
	if (env[i] != '=' && env[i])
		return (0);
	return (1);
}

int	env_arg_control(t_prime *data, char *env)
{
	if (env_name_control(env))
		return (1);
	command_error(env, "export", "not a valid identifier", data);
	data->exit_code = 1;
	return (0);
}
