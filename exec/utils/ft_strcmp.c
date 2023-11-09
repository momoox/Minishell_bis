/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:21:38 by oliove            #+#    #+#             */
/*   Updated: 2023/11/08 23:32:26 by oliove           ###   ########.fr       */
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



char	*ft_strdup_pipe(t_mall *mall, char *src)
{
	char	*dst;

	dst = malloc_plus_plus(&mall, sizeof(char) * (ft_strlen(src) + 1));
	if (!dst)
		return (0);
	ft_strlcpy(dst, src, ft_strlen(src) + 1);
	dst[ft_strlen(src)] = '\0';
	return (dst);
}

char	*ft_substr_pipe(t_mall *mall, char *s, int start, int len)
{
	char	*str;
	int		i;
	int		slen;

	slen = 0;
	i = 0;
	if (!s || start < 0)
		return (0);
	if (start >= ft_strlen(s))
		slen = 0;
	else
		while (s[start + slen] != '\0' && slen < len)
			slen++;
	str = malloc_plus_plus(&mall, sizeof(char) * (slen) + 1);
	if (!str)
		return (0);
	if (slen != 0)
	{
		while (s[start] != '\0' && i + 1 <= len)
			str[i++] = s[start++];
	}
	str[i] = '\0';
	return (str);
}
