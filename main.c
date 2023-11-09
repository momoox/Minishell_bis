/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:40:29 by mgeisler          #+#    #+#             */
/*   Updated: 2023/11/09 20:49:57 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reader(t_data *data, t_mall *mall)
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
			//free(data->input);
			continue ;
		}
		add_history(data->input);
		parser(data, mall);
		run_exec(data, mall);
		//free(data->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_mall	mall;

	(void)argc;
	(void)argv;
	init_data(&data);
	tab_env(&mall, &data, env);
	reader(&data, &mall);
}
