/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:13:21 by momox             #+#    #+#             */
/*   Updated: 2023/11/04 20:54:45 by momox            ###   ########.fr       */
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

void	env_check(t_mall *mall, t_data *data)
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
			var_env = get_env(mall, temp->content, env_len);
			replace = identify_replace(mall, data, var_env);
			temp->content = replace_env(mall, temp->content, replace);
		}
		temp = temp->next;
	}
}
