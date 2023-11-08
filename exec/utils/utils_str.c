/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:47:57 by oliove            #+#    #+#             */
/*   Updated: 2023/11/03 19:51:26 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

int	ft_strlen_pipe(const char *str)
{
	int	i;

	if (!str)
		return (EXIT_FAILURE);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd_pipe(char *str, int fd)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}

char	*ft_strjoin_pipe(t_mall *mall, char const *s1, char const *s2)
{
	char	*res;
	int		len1;
	int		len2;
	int		i;

	i = 0;
	len1 = ft_strlen_pipe(s1);
	len2 = ft_strlen_pipe(s2);
	res = malloc_plus_plus(&mall, sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (NULL);
	if (!s1 && !s2)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
		res[len1++] = s2[i++];
	res[len1] = '\0';
	return (res);
}
char	*ft_strjoin_pipe2(t_mall *mall, char const *s1, char const *s2)
{
	char	*res;
	int		len1;
	int		len2;
	int		i;

	i = 0;
	len1 = ft_strlen_pipe(s1);
	len2 = ft_strlen_pipe(s2);
	res = malloc_plus_plus(&mall, sizeof(char) * (len1 + len2 + 2));
	if (!res)
		return (NULL);
	if (!s1 && !s2)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 32;
	i = 0;
	while (s2[i])
		res[len1++] = s2[i++];
	res[len1] = '\0';
	return (res);
}

void	ft_putstr_fd_jump(char *str, int fd)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}
