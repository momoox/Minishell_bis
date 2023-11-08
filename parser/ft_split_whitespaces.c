/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:46:47 by momox             #+#    #+#             */
/*   Updated: 2023/11/03 19:43:42 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(char *s)
{
	int	i;
	int	words;

	if (s[0] && !s[1])
		return (1);
	words = 0;
	i = 1;
	while (s[i])
	{
		if (ft_whitespace(s[i]) && is_between_quote(s, i) == '0'
			&& !ft_whitespace(s[i - 1]))
			words++;
		i++;
	}
	words++;
	return (words);
}

int	lenword(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i] && is_between_quote(s, i) == '0' && ft_whitespace(s[i]))
		i++;
	while (s[i] && (is_between_quote(s, i) != '0' || (is_between_quote(s,
					i) == '0' && !ft_whitespace(s[i]))))
	{
		len++;
		i++;
	}
	return (len);
}

char	*cpyword(t_mall *mall, char *s, int *i, int len)
{
	char	*str;
	int		u;

	u = 0;
	while ((ft_whitespace(s[(*i)]) && is_between_quote(s, *i) == '0'))
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

char	**freeall(char **tab)
{
	int	j;

	j = 0;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split_whitespaces(t_mall *mall, char *s)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	tab = malloc_plus_plus(&mall, sizeof(char *) * (count(s) + 1));
	if (!tab)
		return (0);
	while (j < count(s))
	{
		tab[j++] = cpyword(mall, s, &i, lenword(s, i));
		if (!tab[j - 1])
			return (freeall(tab));
	}
	tab[j] = 0;
	return (tab);
}
