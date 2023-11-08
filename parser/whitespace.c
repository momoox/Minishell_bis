/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:12:59 by momox             #+#    #+#             */
/*   Updated: 2023/11/03 17:47:15 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_whitespaces(char *s)
{
	int	len;
	int	ws;
	int	i;

	len = ft_strlen(s);
	ws = 0;
	i = 0;
	while (s[i])
	{
		if (ft_whitespace(s[i]) == 1)
			ws++;
		i++;
	}
	if (len == ws)
		return (1);
	return (0);
}

int	ft_whitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
