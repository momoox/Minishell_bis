/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:43:09 by momox             #+#    #+#             */
/*   Updated: 2023/10/23 22:24:49 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	len_input(char *s)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (s[i])
// 	{
// 		while (s[i] == ' ')
// 		{
// 			len++;
// 			i++;
// 		}
// 		i++;
// 	}
// 	return (len + 1);
// }

void	print_exec(t_data *data)
{
	int	u;

	u = 0;
	while (data->exec[0].cmd[u])
	{
		printf("tab line = %s\n", data->exec[0].cmd[u]);
		printf("struct = %s\n", data->exec[0].stdin_st->content);
		printf("struct = %s\n", data->exec[0].stdout_st->content);
		u++;
	}
	u = 0;
	while (data->exec[1].cmd[u])
	{
		printf("tab line = %s\n", data->exec[1].cmd[u]);
		printf("struct = %s\n", data->exec[1].stdin_st->content);
		printf("struct = %s\n", data->exec[1].stdout_st->content);
		u++;
	}
}

void	print_tab(t_data *data)
{
	int	i;

	i = 0;
	if (data->env)
	{
		while (data->env[i])
		{
			printf("env = %s\n", data->env[i]);
			i++;
		}
	}
}

void	printtab2(int *tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		printf("%d\n", tab[i]);
}
