/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 23:28:11 by momox             #+#    #+#             */
/*   Updated: 2023/11/04 21:04:26 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit_code(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}

int	len_tmp(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
			return (i);
		i++;
	}
	return (0);
}

void	exit_var_next(t_mall *mall, char *start_len, t_list *temp, char *nb)
{
	int	len;

	len = len_tmp(temp->content);
	start_len = ft_substr(mall, temp->content, 0, len);
	temp->content = ft_substr(mall, temp->content, (len + 2),
			ft_strlen(temp->content) - (len + 2));
	nb = ft_strjoin(mall, start_len, nb);
	temp->content = ft_strjoin(mall, nb, temp->content);
}

void	check_exit_var(t_mall *mall, t_data *data)
{
	t_list	*temp;
	char	*nb;
	int		len;
	char	*start_len;

	temp = data->list;
	nb = NULL;
	while (temp)
	{
		if (is_exit_code(temp->content) == 1)
		{
			len = len_tmp(temp->content);
			nb = ft_itoa(mall, data->exit_code);
			if (len > 0)
				exit_var_next(mall, start_len, temp, nb);
			else
			{
				start_len = ft_substr(mall, temp->content, 2,
						ft_strlen(temp->content) - 2);
				temp->content = ft_strjoin(mall, nb, start_len);
			}
		}
		temp = temp->next;
	}
}
