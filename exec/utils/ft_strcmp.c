/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:21:38 by oliove            #+#    #+#             */
/*   Updated: 2023/10/22 00:38:51 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		EXIT_FAILURE;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*ss1;
// 	unsigned char	*ss2;

// 	if (!s1 || !s2)
// 		EXIT_FAILURE;
// 	ss1 = (unsigned char *)s1;
// 	ss2 = (unsigned char *)s2;
// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	while (n--)
// 	{
// 		if (ss1[i] != ss2[i] || ss1[i] == 0 || ss2[i] == 0)
// 			return (ss1[i] - ss2[i]);
// 		i++;
// 	}
// 	return (0);
// }
