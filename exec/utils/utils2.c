/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 03:41:21 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 03:49:15 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*i;

	i = (unsigned char *)s;
	while (n > 0)
	{
		*i++ = '\0';
		n--;
	}
}

void	*ft_calloc_env(t_data *data, size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc_plus_plus(&data->mall, count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	**realloc_env(t_data *data, size_t size)
{
	char	**new_env;
	size_t	i;

	new_env = ft_calloc_env(data, size + 1, sizeof *new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(data, data->env[i]);
		//free_tmp(data->env[i]);
		i++;
	}
	// //free(data->env);
	return (new_env);
}
