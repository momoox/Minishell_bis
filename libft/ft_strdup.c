/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:05:04 by momox             #+#    #+#             */
/*   Updated: 2023/11/03 19:26:22 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (ft_strlen(src));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(t_mall *mall, char *src)
{
	char	*dst;

	dst = malloc_plus_plus(&mall, sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (0);
	ft_strlcpy(dst, src, ft_strlen(src) + 1);
	dst[ft_strlen(src)] = '\0';
	return (dst);
}
