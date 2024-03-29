/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:21:33 by momox             #+#    #+#             */
/*   Updated: 2023/11/30 10:14:30 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

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
	if (!tokenize(data))
		return (0);
	if (!check_token(data))
		return (0);
	check_quote_remove(data, data->list);
	cmd_tab(data);
	tab_exec(data);
	if (data->flag_delete == 1)
		return (0);
	return (1);
}

	// if (!(ft_strncmp(data->input, "<<", 2)))
	// print_debug(data);
	// 	split_hd(data, data->list);
	// print_exec(data);
	// print_list(data->list);
	// print_token(data->list);
	// print_exec(data);
