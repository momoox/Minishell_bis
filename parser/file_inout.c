/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_inout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:55:40 by momox             #+#    #+#             */
/*   Updated: 2023/10/21 22:26:58 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_error_check(t_list *temp)
{
	if ((temp->token == REDIR_IN || temp->token == REDIR_OUT
			|| temp->token == REDIR_APPEND) && temp->next->token != FILES)
		printf("minishell: syntax error near unexpected token `%s'\n",
			temp->content);
}

void	file_inout(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp && temp->next)
	{
		if (temp->token == REDIR_IN && temp->next->token == FILES)
		{
			temp->next->token = REDIR_IN;
			temp = temp->next;
		}
		else if (temp->token == REDIR_OUT && temp->next->token == FILES)
		{
			temp->next->token = REDIR_OUT;
			temp = temp->next;
		}
		else if (temp->token == REDIR_APPEND && temp->next->token == FILES)
		{
			temp->next->token = REDIR_APPEND;
			temp = temp->next;
		}
		else
			redir_error_check(temp);
		temp = temp->next;
	}
}
