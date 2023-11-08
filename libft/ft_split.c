/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 17:43:46 by momox             #+#    #+#             */
/*   Updated: 2023/11/03 19:27:53 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_split(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			words++;
		i++;
	}
	return (words);
}

size_t	lenword_split(const char *s, size_t i, char c)
{
	size_t	len;

	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

char	*cpyword_split(t_mall *mall, const char *s, size_t *i, char c)
{
	char	*str;
	size_t	len;
	size_t	u;

	u = 0;
	len = lenword_split(s, *i, c);
	while (s[*i] == c)
		(*i)++;
	str = malloc_plus_plus(&mall, sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (len)
	{
		str[u++] = s[(*i)++];
		len--;
	}
	str[u] = '\0';
	return (str);
}

char	**freeall_split(char **tab)
{
	size_t	j;

	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(t_mall *mall, char *s, char c)
{
	size_t		i;
	size_t		j;
	char		**tab;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	tab = malloc_plus_plus(&mall, sizeof(char *) * (count_split(s, c) + 1));
	if (!tab)
		return (0);
	while (j < count_split(s, c))
	{
		tab[j++] = cpyword_split(mall, s, &i, c);
		if (!tab[j - 1])
			return (freeall_split(tab));
	}
	tab[j] = 0;
	return (tab);
}
