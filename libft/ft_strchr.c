/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:48:58 by momox             #+#    #+#             */
/*   Updated: 2023/10/21 22:21:49 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *str, int search)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)search)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)search)
		return ((char *)&str[i]);
	return (NULL);
}
