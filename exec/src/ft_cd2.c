/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:53:37 by oliove            #+#    #+#             */
/*   Updated: 2023/11/22 19:34:10 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"


void	init_data_shell(t_data *data)
{
	data->shell = malloc_plus_plus(&data->mall, sizeof(t_exec_shell));
	data->shell->cwd = ft_strdup(data, ft_my_var(data, "PWD"));
	data->shell->pwd = NULL;
	data->shell->hold_pwd = NULL;
}

