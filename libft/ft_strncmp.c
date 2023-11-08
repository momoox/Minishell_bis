/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:48:07 by momox             #+#    #+#             */
/*   Updated: 2023/10/21 22:22:23 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (0);
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && i != len - 1 && s1[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
