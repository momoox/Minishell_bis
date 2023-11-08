/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:55:12 by oliove            #+#    #+#             */
/*   Updated: 2023/11/03 22:41:10 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

static int	ft_word_count(char const *s, char car)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = car;
	while (s[i] != '\0')
	{
		if (c == car && s[i] != c)
			j++;
		c = s[i];
		i++;
	}
	return (j);
}

static char	*ft_free_sub(char *str)
{
	free(str);
	return (NULL);
}

static char	*ft_substr_mod(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen_pipe(s) - start)
		len = ft_strlen_pipe(s) - start;
	if (start > (unsigned int)ft_strlen_pipe(s))
		len = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (ft_free_sub(dest));
	while (s[i])
	{
		if (i >= (int)start && j < (int)len)
			dest[j++] = s[i];
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

static void	*ft_free(char **tab, int w)
{
	int	i;

	i = 0;
	while (i != w)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split_pipe(t_mall *mall, char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		w;

	i = 0;
	j = 0;
	w = 0;
	tab = (char **)malloc_plus_plus(&mall, sizeof(char *)
			* (ft_word_count(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i] && s[j] && w < ft_word_count(s, c))
	{
		i = j;
		while (s[i] && s[i] == c)
			i++;
		printf("split_pipe : S = [%s]\n",s);
		j = i;
		while (s[j] && s[j] != c)
			j++;
		printf("split_pipe : S = [%s]\n",s);
		tab[w++] = ft_substr_mod(mall, s, i, j - i);
		if (!tab[w - 1])
			return (ft_free(tab, w));
		tab[w] = NULL;
	}
	printf("split_pipe : tab = [%s]\n",*tab);
	return (tab);
}
