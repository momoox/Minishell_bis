/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:38:20 by momox             #+#    #+#             */
/*   Updated: 2023/11/30 09:28:28 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*create_next(t_list *t, t_data *data, int *i)
{
	if (t && t->token == PIPE)
	{
		data->exec[*i + 1].stdin_st = t;
		t = t->next;
	}
	return (t);
}

void	create_tab(t_data *data, t_list *t, t_list *lst, int i)
{
	while (t && ++i < data->nb_exec)
	{
		while (t && t->token != PIPE)
		{
			if (t->token == REDIR_I && t->next && t->next->token == FILES)
				redir_in_manage(data, t, i);
			else if (t->token == COMMAND && data->exec[i].cmd == NULL)
			{
				if (lst->token != COMMAND)
					data->exec[i].cmd = ft_tabdup(data, lst->cmd);
				else
					data->exec[i].cmd = ft_tabdup(data, t->cmd);
			}
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
		t = create_next(t, data, &i);
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
	t_list	*lst;
	int		i;

	temp = data->list;
	lst = data->list;
	i = -1;
	data->nb_exec = count_pipe(temp);
	init_exec(data, data->nb_exec);
	create_tab(data, temp, lst, i);
}
