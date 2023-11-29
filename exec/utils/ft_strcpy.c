/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:18:29 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 17:50:42 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

char *ft_strcpy(char *dest, char *src)
{
	int i;
	
	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	sort_tab(char **tab)
{
	unsigned int	i = 0;
	unsigned int	size = 0;
	char	*temp;
	
	while (tab[size++])
		;
	while (i < (size - 1))
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			temp = tab[i];
			tab[i] = tab[i+ 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}