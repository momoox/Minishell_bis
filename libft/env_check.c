/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:13:21 by momox             #+#    #+#             */
/*   Updated: 2023/11/28 19:48:33 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_pos(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

int	is_env(char *arg)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			i++;
			while ((arg[i] >= 'A' && arg[i] <= 'Z')
				|| (arg[i] >= 'a' && arg[i] <= 'z')
				|| (arg[i] >= '0' && arg[i] <= '9')
				|| arg[i] == '_')
			{
				flag++;
				i++;
			}
			break ;
		}
		i++;
	}
	return (flag);
}

void	env_check(t_data *data)
{
	int		env_len;
	char	*var_env;
	char	*replace;
	t_list	*temp;

	temp = data->list;
	while (temp)
	{
		if (is_env(temp->content) > 0)
		{
			if (is_between_quote(temp->content, 0) == '\''
				&& is_between_quote(temp->content,
					ft_strlen(temp->content) - 2) == '\'')
				break ;
			env_len = is_env(temp->content);
			var_env = get_env(data->mall, temp->content, env_len);
			replace = identify_replace(data->mall, data, var_env);
			temp->content = replace_env(data->mall, temp->content, replace);
			if (!temp->content)
				ft_lstdel_here(&data->list, temp);
		}
		temp = temp->next;
	}
}
