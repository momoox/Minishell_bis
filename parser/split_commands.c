/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 19:04:02 by momox             #+#    #+#             */
/*   Updated: 2023/11/04 20:59:08 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_hd(t_mall *mall, t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp)
	{
		if (!ft_strncmp(temp->content, "<", 1)
			&& !ft_strncmp(temp->next->content, "<", 1))
		{
			temp->content = ft_strjoin(mall, temp->content,
					temp->next->content);
			ft_lstdel_here(&list, temp->next);
		}
		temp = temp->next;
	}
}

int	split_op(t_mall *mall, t_data *data, char c)
{
	int		i;
	t_list	*save;
	t_list	*temp;

	temp = data->list;
	while (temp)
	{
		save = temp;
		data->parsed_line = ft_split_operators(mall, temp->content, c);
		i = -1;
		while (data->parsed_line[++i])
		{
			ft_lstadd_here(&temp,
				ft_lstnew(mall, ft_strdup(mall, data->parsed_line[i])));
			temp = temp->next;
		}
		temp = temp->next;
		ft_lstdel_here(&data->list, save);
	}
	return (0);
}

void	split_line(t_mall *mall, t_data *data)
{
	int		i;
	char	*tab;
	t_list	*temp;

	i = -1;
	data->parsed_line = ft_split_whitespaces(mall, data->input);
	while (data->parsed_line[++i])
	{
		tab = ft_strdup(mall, data->parsed_line[i]);
		if (!tab)
			return ;
		temp = ft_lstnew(mall, tab);
		if (!temp)
			return ;
		lstadd_back(&data->list, temp);
	}
	list_back(data->list);
}
