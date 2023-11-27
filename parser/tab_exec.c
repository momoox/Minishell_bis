/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:38:20 by momox             #+#    #+#             */
/*   Updated: 2023/11/23 23:02:58 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_tab(t_data *data, t_list *temp, int i)
{
	while (temp && i < data->nb_exec)
	{
		while (temp && temp->next && temp->token != PIPE)
		{
			if (temp->token == REDIR_IN && temp->next->token == FILES)
				redir_in_manage(data, temp, i);
			else if (temp->token == COMMAND && data->exec[i].cmd == NULL)
				data->exec[i].cmd = temp->cmd;
			else if (temp->token == REDIR_OUT && temp->next->token == FILES)
				redir_out_manage(data, temp, i);
			else if (temp->token == REDIR_APPEND && temp->next->token == FILES)
				redir_append_manage(data, temp, i);
			else if (temp->token == PIPE && data->exec[i].stdin_st == NULL)
				data->exec[i].stdin_st = temp;
			else if (temp->token == PIPE && data->exec[i].stdout_st == NULL)
				data->exec[i].stdout_st = temp;
			temp = temp->next;
		}
		if (temp && temp->token == PIPE)
		{
			data->exec[i + 1].stdin_st = temp;
			temp = temp->next;
		}
		i++;
	}
}

void	init_exec(t_data *data, int nb_pipe)
{
	int	i;

	i = 0;
	data->exec = malloc_plus_plus(&data->mall, sizeof(t_exec) * (nb_pipe + 1));
	while (i < nb_pipe)
	{
		data->exec[i].cmd = NULL;
		data->exec[i].stdin_st = NULL;
		data->exec[i].stdout_st = NULL;
		i++;
	}
}

int	count_pipe(t_list *list)
{
	t_list	*temp;
	int		nb_pipe;

	temp = list;
	nb_pipe = 0;
	while (temp)
	{
		if (temp->token == PIPE)
			nb_pipe++;
		temp = temp->next;
	}
	return (nb_pipe + 1);
}

void	tab_exec(t_data *data)
{
	t_list	*temp;
	int		i;

	temp = data->list;
	i = 0;
	data->nb_exec = count_pipe(temp);
	printf("in tab_exec %d\n",data->nb_exec);
	init_exec(data, data->nb_exec);
	create_tab(data, temp, i);
}
