/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:02:40 by momox             #+#    #+#             */
/*   Updated: 2023/11/03 19:27:25 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(t_mall *mall, char *s, int start, int len)
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
