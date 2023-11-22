/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:40:29 by mgeisler          #+#    #+#             */
/*   Updated: 2023/11/21 21:23:40 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reader(t_data *data)
{
	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		reinit(data);
		data->input = readline("minishell> ");
		if (!data->input)
			break ;
		if (data->input[0] == 0)
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		parser(data);
		run_exec(data);
		free(data->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	// t_mall	*mall;

	(void)argc;
	(void)argv;
	init_data(&data);
	// mall = NULL;
	tab_env(&data, env);
	reader(&data);
}
