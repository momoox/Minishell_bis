/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_addback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 21:38:43 by momox             #+#    #+#             */
/*   Updated: 2023/11/09 20:49:57 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tabadd_back(t_mall *mall, char **tab, char *new_str)
{
	int		len;
	int		i;
	char	**new_tab;

	if (!tab || !new_str)
		return (NULL);
	len = 0;
	while (tab[len])
		len++;
	new_tab = malloc_plus_plus(&mall, sizeof(char *) * (len + 2));
	if (!new_tab)
		return (NULL);
	i = -1;
	while (tab[++i])
		new_tab[i] = tab[i];
	new_tab[i] = new_str;
	new_tab[i + 1] = NULL;
	//free(tab);
	return (new_tab);
}
