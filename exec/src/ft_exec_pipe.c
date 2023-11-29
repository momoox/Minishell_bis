/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:47:43 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 20:41:47 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

int	ft_pipe2(t_exec *ex, int *fd_stdin, int *fd_stdout)
{
	int	cmd1;
	int	i;
	int	fd[2];

	cmd1 = 1;
	i = 0;
	if (ex->stdin_st && ex->stdin_st->token == REDIR_I)
	{
		close(*fd_stdin);
		*fd_stdin = file_o(ex->stdin_st->content, ex->stdin_st->token);
	}
	if (*fd_stdin == -1)
		cmd1 = 0;
	if (ex->stdout_st && (ex->stdout_st->token == REDIR_O
			|| ex->stdout_st->token == REDIR_A))
	{
		close(*fd_stdout);
		*fd_stdout = file_o(ex->stdout_st->content, ex->stdout_st->token);
	}
	if (!cmd1)
		norm_cmd(&i, fd, fd_stdin);
	return (i);
}

int	norm_cmd(int *i, int fd[], int *fd_stdin)
{
	*i += 1;
	pipe(fd);
	close(fd[1]);
	*fd_stdin = fd[0];
	return (*i);
}

int	ft_lstsize(t_list *list)
{
	int	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	is_forck(t_data *data, t_exec *cmd)
{
	builtin_func	func;

	func = find_builtin(cmd->cmd[0], data->func);
	if (func != NULL)
	{
		if (ft_strncmp(cmd->cmd[0], "export", 7) == 0 && cmd->cmd[1] == NULL)
			return (0);
		else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
			return (0);
		else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
			return (0);
		return (1);
	}
	return (0);
}
