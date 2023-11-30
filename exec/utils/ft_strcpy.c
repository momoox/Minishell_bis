/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:18:29 by oliove            #+#    #+#             */
/*   Updated: 2023/11/30 21:10:51 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

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

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

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
	unsigned int	i;
	unsigned int	size;
	char			*temp;

	i = 0;
	size = 0;
	while (tab[size++])
		;
	while (i < (size - 1))
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

int	errmsg_cmd(t_data *data, char *msg_err[3], int error_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(msg_err[0]);
	msg = ft_strdup_pipe(data, "minishell: ");
	if (msg_err[0])
	{
		msg = join_strs(data, msg, msg_err[0]);
		msg = join_strs(data, msg, ": ");
	}
	if (msg[1])
	{
		if (detail_quotes)
			msg = join_strs(data, msg, "`");
		msg = join_strs(data, msg, msg_err[1]);
		if (detail_quotes)
			msg = join_strs(data, msg, "'");
		msg = join_strs(data, msg, ": ");
	}
	msg = join_strs(data, msg, msg_err[2]);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (error_nb);
}
