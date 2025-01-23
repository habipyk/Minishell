/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyalcink <hyalcink@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 08:01:03 by sbozan            #+#    #+#             */
/*   Updated: 2024/01/10 22:57:15 by hyalcink         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	prime_init(t_prime *data)
{
	data->fd = NULL;
	data->line = NULL;
	data->lexer = NULL;
	data->expander = NULL;
	data->parser = NULL;
}

void	ft_readline(t_prime *data)
{
	while (1)
	{
		prime_init(data);
		data->line = readline("minishell> ");
		if (data->line && *data->line != 0)
			add_history(data->line);
		if (data->line == NULL)
		{
			printf("minishell> exit\n");
			exit(data->exit_code);
		}
		lexer(data);
		expander(data);
		parser(data);
		executer(data, 0);
		free_prime(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_prime	*data;

	(void)argc;
	(void)argv;
	data = (t_prime *)malloc(sizeof(t_prime));
	data->env_l = NULL;
	data->exit_code = 0;
	g_signal = 0;
	env_init(data, env);
	signal_init();
	ft_readline(data);
}
