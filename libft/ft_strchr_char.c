/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:06:19 by momox             #+#    #+#             */
/*   Updated: 2023/11/29 20:10:41 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr_char(const char *str, char *s)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (s[u] && str[i])
	{
		if (str[i] == s[u])
		{
			while (str[i] == s[u] && s[u] && str[i])
			{
				u++;
				i++;
				if (!s[u])
					return (1);
			}
		}
		if (str[i])
			i++;
	}
	return (0);
}
