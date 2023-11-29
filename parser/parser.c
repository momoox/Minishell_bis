/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:21:33 by momox             #+#    #+#             */
/*   Updated: 2023/11/29 03:24:26 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_data *data)
{
	if (check_whitespaces(data->input) == 1)
		return (0);
	if (check_quote(data->input, data) != '0')
		return (0);
	if (!check_char(data->input, data))
		return (0);
	split_line(data);
	check_exit_var(data);
	env_check(data);
	if (ft_strchr(data->input, '|'))
		split_op(data, '|');
	if (ft_strchr(data->input, '<'))
		split_op(data, '<');
	if (ft_strchr(data->input, '>'))
		split_op(data, '>');
	if (!(ft_strncmp(data->input, "<<", 2)))
		split_hd(data, data->list);
	tokenize(data);
	check_quote_remove(data, data->list);
	cmd_tab(data);
	tab_exec(data);
	if (data->flag_delete != 0)
		return (0);
	return (1);
}

	// print_list(data->list);
	// print_exec(data);
	// print_token(data->list);
	// print_exec(data);
