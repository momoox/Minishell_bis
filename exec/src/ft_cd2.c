/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:53:37 by oliove            #+#    #+#             */
/*   Updated: 2023/11/28 01:53:55 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"


void	init_data_shell(t_data *data)
{
	data->shell = malloc_plus_plus(&data->mall, sizeof(t_exec_shell));
	data->shell->cwd = ft_strdup(data, ft_my_var(data, "PWD"));
	data->shell->old_pwd = ft_strdup(data, ft_my_var(data, "OLDPWD"));
}

