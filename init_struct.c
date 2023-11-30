/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 21:07:04 by momox             #+#    #+#             */
/*   Updated: 2023/11/30 02:09:11 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->input = NULL;
	data->parsed_line = NULL;
	data->env = NULL;
	data->flag_unlink = 0;
	data->flag_delete = 0;
	data->list = NULL;
	data->nb_exec = 0;
	data->exit_code = 0;
	data->pid = -1;
	data->mall = NULL;
	data->func = get_builting(data);
}

void	reinit(t_data *data)
{
	data->input = NULL;
	data->parsed_line = NULL;
	data->flag_unlink = 0;
	data->flag_delete = 0;
	data->list = NULL;
	data->nb_exec = 0;
}
