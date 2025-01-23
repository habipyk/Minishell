/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 00:11:56 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*get_oldpwd(t_env_l *env, char *path)
{
	t_env_l	*temp_env;

	temp_env = env;
	while (temp_env)
	{
		if (!ownstrcmp(temp_env->name, path))
			return (temp_env->content);
		temp_env = temp_env->next;
	}
	return (NULL);
}

int	update_env(t_prime *data, char *env_name, char *new_arg)
{
	t_env_l	*env;
	char	*temp_str;

	env = data->env_l;
	temp_str = NULL;
	while (env)
	{
		if (!ownstrcmp(env->name, env_name))
		{
			if (env->content)
				free(env->content);
			env->content = NULL;
			if (!new_arg)
				return (1);
			env->content = ft_strjoin(env->content, new_arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

char	*get_env_name(char *content)
{
	char	*name;
	int		i;

	i = 0;
	while (content[i] && content[i] != '=')
		i++;
	name = ft_substr(content, 0, i);
	return (name);
}

void	add_newenv(t_prime *data, char *env)
{
	char	*content;
	char	*name;

	name = get_env_name(env);
	content = env + ft_strlen(name);
	if (*content == '=' && *(content + 1))
		content = ft_strdup(content + 1);
	else
		content = NULL;
	env_lstadd_back(&data->env_l, env_listnew(name, content));
}
