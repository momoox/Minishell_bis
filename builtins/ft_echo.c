/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:21:42 by momox             #+#    #+#             */
/*   Updated: 2023/10/22 20:10:40 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '-' && str[i + 1] == 'n')
		{
			i++;
			while (str[i])
			{
				if (str[i] && str[i] != 'n')
					return (0);
				i++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_echo_2(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if (cmd[i])
			printf(" ");
	}
	printf("\n");
}

int	ft_echo(char **cmd)
{
	int	i;

	if (!cmd[1])
	{
		printf("\n");
		return (0);
	}
	if (check_n(cmd[1]) == 1)
	{
		i = 1;
		while (check_n(cmd[i]) == 1)
			i++;
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			i++;
			if (cmd[i])
				printf(" ");
		}
	}
	else
		ft_echo_2(cmd);
	return (0);
}
