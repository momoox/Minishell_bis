/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:40:29 by mgeisler          #+#    #+#             */
/*   Updated: 2023/11/29 23:14:14 by momox            ###   ########.fr       */
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
		data->input = readline("minishell> ");
		if (!data->input)
			break ;
		if (data->input[0] == 0)
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		if (!parser(data))
		{
			free(data->input);
			continue ;
		}
		run_exec(data);
		free(data->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		exit;

	(void)argc;
	(void)argv;
	init_data(&data);
	tab_env(&data, env);
	reader(&data);
	printf("\033[1A\033[11Cexit\n");
	exit = data.exit_code;
	free_mall(&data.mall);
	return (exit);
}
