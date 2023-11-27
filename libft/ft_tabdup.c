/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:49:54 by momox             #+#    #+#             */
/*   Updated: 2023/11/27 18:51:16 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tabdup(t_data *data, char **tab)
{
	int		i;
	char	**new_tab;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
		i++;
	new_tab = malloc_plus_plus(&data->mall, sizeof(char *) * (i + 1));
	if (!new_tab)
		return (perror("Malloc"), NULL);
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(data, tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
