/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 23:18:53 by momox             #+#    #+#             */
/*   Updated: 2023/11/08 23:46:35 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_error(t_data *data, t_list *list)
{
	data->flag_delete = 1;
	if (!list->next)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(list->next->content, 2);
		ft_putstr_fd("'\n", 2);
	}
}

void	redir_in_manage(t_mall *mall, t_data *data, t_list *list)
{
	int		fd;
	char	*error_msg;

	if (!list->next || list->next->token != FILES)
		redir_error(data, list);
	fd = open(list->next->content, O_RDONLY);
	if (fd == -1)
	{
		data->exit_code = 1;
		error_msg = ft_strjoin(mall, "Minishell: ", list->next->content);
		perror(error_msg);
		return ;
	}
	close(fd);
}

void	redir_out_manage(t_mall *mall, t_data *data, t_list *list)
{
	int		fd;
	char	*error_msg;

	if (!list->next || list->next->token != FILES)
		redir_error(data, list);
	fd = open(list->next->content, O_WRONLY, O_CREAT, O_TRUNC, 0644);
	if (fd == -1)
	{
		data->exit_code = 1;
		error_msg = ft_strjoin(mall, "Minishell: ", list->next->content);
		perror(error_msg);
		return ;
	}
	close(fd);
}

void	redir_append_manage(t_mall *mall, t_data *data, t_list *list)
{
	int		fd;
	char	*error_msg;

	if (!list->next || list->next->token != FILES)
		redir_error(data, list);
	fd = open(list->next->content, O_WRONLY, O_CREAT, O_APPEND, 0644);
	if (fd == -1)
	{
		data->exit_code = 1;
		error_msg = ft_strjoin(mall, "Minishell: ", list->next->content);
		perror(error_msg);
		return ;
	}
	close(fd);
}
