/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_execve_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:11:45 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**get_env_cpy(t_prime *data)
{
	char	**envlist;
	char	*temp_env;
	t_env_l	*temp_envlist;

	envlist = NULL;
	temp_envlist = data->env_l;
	while (temp_envlist)
	{
		if (temp_envlist->content)
		{
			temp_env = NULL;
			temp_env = ft_strjoin(temp_env, temp_envlist->name);
			temp_env = ft_strjoin(temp_env, "=");
			temp_env = ft_strjoin(temp_env, temp_envlist->content);
			envlist = dynamic_malloc(envlist, temp_env);
		}
		temp_envlist = temp_envlist->next;
	}
	return (envlist);
}

int	search_path(t_env_l *env_l, char *str)
{
	t_env_l	*temp_env;

	temp_env = env_l;
	while (temp_env)
	{
		if (!ownstrcmp(temp_env->name, str))
		{
			if (!ownstrcmp(temp_env->name, "PWD"))
				if (temp_env->content[0] != '/')
					return (0);
			return (1);
		}
		temp_env = temp_env->next;
	}
	return (0);
}

char	**path_create(t_prime *data, t_parser *pars, char **path)
{
	int	i;

	if (pars->command && pars->command[0] == '/')
	{
		i = -1;
		while (data->path && data->path[++i])
			path = dynamic_malloc(path, pars->command);
		return (path);
	}
	i = -1;
	while (data->path && data->path[++i])
		path = dynamic_malloc(path, ft_strjoin(data->path[i],
					pars->command));
	return (path);
}

char	*get_command(t_prime *data, t_parser *pars)
{
	char	**path;
	int		i;
	char	*command;
	char	cwd[256];

	path = NULL;
	path = path_create(data, pars, path);
	i = -1;
	command = pars->command;
	while (path && path[++i])
		if (!access(path[i], F_OK) && !access(path[i], X_OK))
			break ;
	if (path && path[i])
		command = ft_strdup(path[i]);
	if (!search_path(data->env_l, "PATH"))
		command = pars->command;
	if (pars->command && pars->command[0] == '.' && pars->command[1] == '/')
	{
		command = ft_strdup(getcwd(cwd, 256));
		command = ft_strjoin(command, ft_substr(pars->command, 1,
					ft_strlen(pars->command) - 1));
	}
	double_str_free(path);
	return (command);
}
