/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:28:47 by momox             #+#    #+#             */
/*   Updated: 2023/11/27 20:08:22 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_list *list)
{
	while (list)
	{
		if (list->token == PIPE)
			printf("%s = PIPE\n", list->content);
		if (list->token == COMMAND)
			printf("%s = COMMAND\n", list->content);
		if (list->token == REDIR_I)
			printf("%s = REDIR IN\n", list->content);
		if (list->token == REDIR_O)
			printf("%s = REDIR OUT\n", list->content);
		if (list->token == REDIR_A)
			printf("%s = REDIR APPEND\n", list->content);
		if (list->token == FILES)
			printf("%s = FILES\n", list->content);
		list = list->next;
	}
}
