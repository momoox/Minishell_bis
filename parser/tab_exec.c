/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:38:20 by momox             #+#    #+#             */
/*   Updated: 2023/11/29 01:33:05 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_tab(t_data *data, t_list *t, int i)
{
	while (t && i < data->nb_exec)
	{
		while (t && t->token != PIPE)
		{
			if (t->token == REDIR_I && t->next && t->next->token == FILES)
				redir_in_manage(data, t, i);
			else if (t->token == COMMAND && data->exec[i].cmd == NULL)
				data->exec[i].cmd = ft_tabdup(data, t->cmd);
			else if (t->token == REDIR_O && t->next && t->next->token == FILES)
				redir_out_manage(data, t, i);
			else if (t->token == REDIR_A && t->next && t->next->token == FILES)
				redir_append_manage(data, t, i);
			else if (t->token == PIPE && data->exec[i].stdin_st == NULL)
				data->exec[i].stdin_st = t;
			else if (t->token == PIPE && data->exec[i].stdout_st == NULL)
				data->exec[i].stdout_st = t;
			t = t->next;
		}
		if (t && t->token == PIPE)
		{
			data->exec[i + 1].stdin_st = t;
			t = t->next;
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
	printf("nb_)ec %d\n",nb_pipe);
	return (nb_pipe + 1);
}

void	tab_exec(t_data *data)
{
	t_list	*temp;
	int		i;

	temp = data->list;
	i = 0;
	data->nb_exec = count_pipe(temp);
	init_exec(data, data->nb_exec);
	create_tab(data, temp, i);
}
