/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:53:00 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env_l	*env_listnew(char *name, char *content)
{
	t_env_l	*new;

	new = (t_env_l *)malloc(sizeof(t_env_l));
	if (!new)
		return (0);
	new->name = name;
	new->content = content;
	new->next = 0;
	return (new);
}

t_env_l	*env_lstlast(t_env_l	*lst)
{
	t_env_l	*temp;

	if (!lst)
		return (0);
	temp = lst;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	env_lstadd_back(t_env_l	**lst, t_env_l	*new)
{
	if (new)
	{
		if (!(*lst))
		{
			*lst = new;
			return ;
		}
		env_lstlast(*lst)->next = new;
		new->next = 0;
	}
}

void	path_init(t_prime *data)
{
	t_env_l	*env_l;
	int		i;
	char	**temp_command;
	char	*join;

	env_l = data->env_l;
	data->path = NULL;
	if (!search_path(env_l, "PATH"))
		return ;
	while (env_l)
	{
		if (!ownstrcmp(env_l->name, "PATH"))
			break ;
		env_l = env_l->next;
	}
	temp_command = ft_split(env_l->content, ':');
	i = -1;
	while (temp_command[++i])
	{
		join = ft_strjoin(temp_command[i], "/");
		data->path = dynamic_malloc(data->path, join);
		free(join);
	}
	free(temp_command);
}

void	env_init(t_prime *data, char **env)
{
	int		i;
	int		start;
	int		end;
	char	*name;
	char	*content;

	i = -1;
	while (env && env[++i])
	{
		end = 0;
		while (env[i][end])
		{
			start = end;
			while (env[i][end] && env[i][end] != '=')
				end++;
			name = ft_substr(env[i], start, end);
			end++;
			start = end;
			while (env[i][end])
				end++;
			content = ft_substr(env[i], start, end);
			env_lstadd_back(&data->env_l, env_listnew(name, content));
		}
	}
	path_init(data);
}
