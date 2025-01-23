/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 01:00:42 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	update_pwd_from_export(t_prime *data, char *pwd_name, char *pwd_content)
{
	char	*temp_pwd;

	if (!update_env(data, pwd_name, pwd_content))
	{
		temp_pwd = NULL;
		temp_pwd = ft_strjoin(temp_pwd, pwd_name);
		temp_pwd = ft_strjoin(temp_pwd, "=");
		temp_pwd = ft_strjoin(temp_pwd, pwd_content);
		add_newenv(data, temp_pwd);
		free(temp_pwd);
		return (0);
	}
	return (1);
}

int	change_dir(t_prime *data, char *parameters)
{
	char	pwd[256];
	char	*oldpwd;
	int		error;

	oldpwd = ft_strdup(getcwd(pwd, 256));
	error = chdir(parameters);
	if (!error && !search_path(data->env_l, "OLDPWD"))
		env_lstadd_back(&data->env_l, env_listnew(ft_strdup("OLDPWD"),
				ft_strdup(oldpwd)));
	if (error == -1)
	{
		oldpwd = free_null(oldpwd);
		return (0);
	}
	if (!error && !ownstrcmp(data->parser->parameters[1], "-"))
		printf("%s\n", parameters);
	update_pwd_from_export(data, "PWD", getcwd(pwd, 256));
	update_pwd_from_export(data, "OLDPWD", oldpwd);
	oldpwd = free_null(oldpwd);
	return (1);
}

void	cd_two_arg(t_prime *data)
{
	char	*path;

	path = NULL;
	if (!ownstrcmp(data->parser->parameters[1], "-"))
	{
		if (!search_path(data->env_l, "OLDPWD"))
			if (command_error(0, "cd", "OLDPWD not set", data))
				return ;
		path = ft_strjoin(path, get_oldpwd(data->env_l, "OLDPWD"));
	}
	else if (!ownstrcmp(data->parser->parameters[1], "--"))
		path = ft_strjoin(path, get_oldpwd(data->env_l, "HOME"));
	else
		path = ft_strjoin(path, data->parser->parameters[1]);
	if (!change_dir(data, path))
	{
		if (*data->parser->parameters[1] == '-')
			command_error(data->parser->parameters[1], "cd",
				"invalid option", data);
		else
			command_error(data->parser->parameters[1], "cd",
				" No such file or directory", data);
	}
	free(path);
}

void	cd_one_arg(t_prime *data)
{
	t_env_l	*temp_env;
	char	*content;

	temp_env = data->env_l;
	while (temp_env)
	{
		if (!ownstrcmp("HOME", temp_env->name))
		{
			content = temp_env->content;
			if (!content)
				return ;
			change_dir(data, content);
			return ;
		}
		temp_env = temp_env->next;
	}
	command_error(0, "cd", "HOME not set\n", data);
}

void	run_cd(t_prime *data)
{
	int	param_count;

	data->exit_code = 0;
	param_count = parameters_count(data->parser->parameters);
	if (!search_path(data->env_l, "PWD"))
		delete_env(data, "PWD");
	if (param_count > 1)
		cd_two_arg(data);
	else
		cd_one_arg(data);
}
