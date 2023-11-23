/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:06:19 by momox             #+#    #+#             */
/*   Updated: 2023/11/23 23:14:00 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr_char(const char *str, char *s)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (str[i])
	{
		if (str[i] == s[u])
		{
			while (str[i] == s[u] && s[u])
			{
				u++;
				i++;
				if (!s[u])
					return (1);
			}
		}
		i++;
	}
	return (0);
}