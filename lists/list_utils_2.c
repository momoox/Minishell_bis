/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 22:48:56 by momox             #+#    #+#             */
/*   Updated: 2023/10/21 22:27:55 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_here(t_list **lst, t_list *new)
{
	if (!*lst)
	{
		new->prev = 0;
		(*lst) = new;
	}
	else
	{
		new->prev = (*lst);
		if ((*lst)->next)
		{
			new->next = (*lst)->next;
			(*lst)->next->prev = new;
		}
		else
			new->next = NULL;
		(*lst)->next = new;
	}
}

void	ft_lstdel_here(t_list **first, t_list *delete)
{
	if (!first || !*first || !delete)
		return ;
	if (*first == delete)
		*first = delete->next;
	if (delete->next)
		delete->next->prev = delete->prev;
	if (delete->prev)
		delete->prev->next = delete->next;
	free(delete);
}

int	size_list_string(t_list *list)
{
	t_list	*temp;
	int		total_len;

	temp = list;
	total_len = 0;
	while (temp)
	{
		total_len += ft_strlen(temp->content);
		temp = temp->next;
	}
	return (total_len);
}
