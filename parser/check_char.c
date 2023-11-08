/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 03:19:13 by momox             #+#    #+#             */
/*   Updated: 2023/10/02 03:19:39 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 92 || str[i] == '(' || str[i] == ')'
			|| str[i] == ';'
			|| (str[i] == '&' && str[i + 1] == '&')
			|| (str[i] == '|' && str[i + 1] == '|'))
		{
			printf("minishell: syntax error near unexpected token `%c'\n",
				str[i]);
			data->exit_code = 258;
			return (258);
		}
		i++;
	}
	return (0);
}
