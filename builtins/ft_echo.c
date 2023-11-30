/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:21:42 by momox             #+#    #+#             */
/*   Updated: 2023/11/30 01:35:35 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

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

int	ft_echo(t_data *data, char **cmd)
{
	int	i;

	(void)data;
	if (!cmd[1])
	{
		printf("\n");
		return (CMD_NOT_FOUND);
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
	return (EXIT_SUCCESS);
}
