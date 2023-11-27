/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:40:29 by mgeisler          #+#    #+#             */
/*   Updated: 2023/11/27 18:26:54 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

void	reader(t_data *data)
{
	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		reinit(data);
		data->input = readline("\033[0;33mminishell>\033[0m ");

		if (!data->input)
			break ;
		if (data->input[0] == 0)
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		parser(data);
		//printf("in main : %p\n", &data->exec->cmd[0]);
		run_exec(data);
		free(data->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	// t_mall *mall;
	

	(void)argc;
	(void)argv;
	init_data(&data);
	// data.mall = mall;
	tab_env(&data, env);
	reader(&data); 
}
