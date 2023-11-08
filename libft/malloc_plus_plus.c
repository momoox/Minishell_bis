/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_plus_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:53:53 by momox             #+#    #+#             */
/*   Updated: 2023/11/03 19:41:18 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mall	*ft_lst_new_mall(void *content)
{
	t_mall	*new;

	new = malloc(sizeof(t_mall));
	if (!new)
		return (NULL);
	if (new)
	{
		new->content = content;
		new->next = NULL;
		new->prev = NULL;
	}
	return (new);
}

void	*malloc_plus_plus(t_mall **mall, size_t size)
{
	t_mall			*new;
	size_t			i;
	unsigned char	*ret;

	i = 0;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	while (i < size)
		ret[i++] = 0;
	new = ft_lst_new_mall(ret);
	if (!new)
		return (NULL);
	lstadd_back_mall(mall, new);
	return (ret);
}

void	free_mall(t_mall **mall)
{
	t_mall	*temp;

	while (mall)
	{
		temp = (*mall)->next;
		free((*mall)->content);
		free(*mall);
		*mall = temp;
	}
	free(*mall);
}
