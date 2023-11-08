/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 20:22:16 by momox             #+#    #+#             */
/*   Updated: 2023/11/03 19:43:50 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_op(char *s, char c)
{
	int	i;
	int	words;
	int	op;

	i = 0;
	words = 0;
	op = 0;
	while (s[i])
	{
		if (s[i] != c && (!s[i + 1] || (s[i + 1] == c
					&& is_between_quote(s, i + 1) == '0')))
			words++;
		if (s[i] == c && s[i + 1] == c && is_between_quote(s, i) == '0')
		{
			op++;
			i++;
		}
		else if (s[i] == c && is_between_quote(s, i) == '0')
			op++;
		i++;
	}
	return (words + op);
}

int	lenword_op(char *s, int i, char c)
{
	int	len;
	int	limit;

	len = 0;
	limit = 2;
	if (s[i] == c && is_between_quote(s, i) == '0')
	{
		while (s[i] && s[i] == c && is_between_quote(s, i) == '0' && limit--)
		{
			len++;
			i++;
		}
		return (len);
	}
	while (s[i] && (s[i] != c || is_between_quote(s, i) != '0'))
	{
		len++;
		i++;
	}
	return (len);
}

char	*cpyword_op(t_mall *mall, char *s, int *i, int len)
{
	char	*str;
	int		u;

	u = 0;
	str = malloc_plus_plus(&mall, sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	while (len)
	{
		str[u++] = s[(*i)++];
		len--;
	}
	str[u] = '\0';
	return (str);
}

char	**freeall_op(char **tab)
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

char	**ft_split_operators(t_mall *mall, char *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	tab = malloc_plus_plus(&mall, sizeof(char *) * (count_op(s, c) + 1));
	if (!tab)
		return (0);
	while (j < count_op(s, c))
	{
		tab[j++] = cpyword_op(mall, s, &i, lenword_op(s, i, c));
		if (!tab[j - 1])
			return (freeall_op(tab));
	}
	tab[j] = 0;
	return (tab);
}
