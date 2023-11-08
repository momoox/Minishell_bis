/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:06:13 by momox             #+#    #+#             */
/*   Updated: 2023/10/30 18:45:35 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_list *list)
{
	printf("=====PRINT LIST=====\n");
	while (list)
	{
		printf("list->content = %s\n\n", list->content);
		// if (list->token == FILES)
		// {
		// 	printf("token = %d\n", list->token);
		// }
		// if (list->token == COMMAND && list->cmd)
		// {
		// 	printf("tab 0 = %s\n", list->cmd[0]);
		// 	printf("tab 1 = %s\n", list->cmd[1]);
		// }
		list = list->next;
	}
	printf("====================\n\n");
}
		// if (list->next->next == NULL)
		// printf("list->token = %d\n", list->token);
		// 	return ;