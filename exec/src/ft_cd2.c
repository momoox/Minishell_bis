/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:53:37 by oliove            #+#    #+#             */
/*   Updated: 2023/11/06 00:53:42 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"


void	init_data_shell(t_data *data, t_mall *mall)
{
	data->shell = malloc_plus_plus(&mall, sizeof(t_exec_shell));
	
	data->shell->cwd = ft_strdup(mall, get_env(mall))
	data->shell->pwd = NULL;
	data->shell->hold_pwd = NULL;
}

