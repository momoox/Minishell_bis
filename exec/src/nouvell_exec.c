/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nouvell_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:01:36 by momox             #+#    #+#             */
/*   Updated: 2023/11/30 20:53:28 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

int	initialize_pipes(t_data *data, int fd_pipe[2], int *j)
{
	while ((*j) < data->nb_exec)
	{
		if (*j < data->nb_exec - 1)
		{
			if (pipe(fd_pipe) == -1)
				exit(EXIT_FAILURE);
			data->exec[*j + 1].fd_in = fd_pipe[0];
			data->exec[*j].fd_out = fd_pipe[1];
		}
		else
			data->exec[*j].fd_out = dup(STDOUT_FILENO);
		if (*j == 0)
			data->exec[*j].fd_in = dup(STDIN_FILENO);
		ft_pipe2(&data->exec[*j], &data->exec[*j].fd_in,
			&data->exec[*j].fd_out);
		sig_onoff(0);
		initialize_pipes2(data, j);
		(*j)++;
	}
	cleanup_pipes(data);
	return (1);
}

void	initialize_pipes2(t_data *data, int *j)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		pipe_execution(data, j);
		exit(EXIT_SUCCESS);
	}
	else
	{
		data->exec[*j].pid = pid;
		close(data->exec[*j].fd_in);
		close(data->exec[*j].fd_out);
	}
}

int	pipe_execution(t_data *data, int *j)
{
	int				ret;
	int				i;
	t_builtin_func	func;

	func = find_builtin(data, data->exec[*j].cmd[0]);
	if (func == NULL)
	{
		data->exec[*j].cmd[0] = ft_path_dir(data->mall, data->exec[*j].cmd[0],
				ft_my_var(data, "PATH"), -1);
	}
	dup2(data->exec[*j].fd_out, STDOUT_FILENO);
	dup2(data->exec[*j].fd_in, STDIN_FILENO);
	i = 0;
	while (i < data->nb_exec)
	{
		if (data->exec[i].fd_in > 0)
			close(data->exec[i].fd_in);
		if (data->exec[i].fd_out > 2)
			close(data->exec[i].fd_out);
		i++;
	}
	ret = execute_command(data, &data->exec[*j]);
	sig_onoff(1);
	return (ret);
}

void	cleanup_pipes(t_data *data)
{
	int	status;
	int	i;

	i = data->nb_exec;
	while (--i >= 0)
	{
		waitpid(data->exec[i].pid, &status, 0);
		if (i == data->nb_exec -1)
			data->exit_code = WEXITSTATUS(status);
	}
}

void	ft_pipe(t_data *data)
{
	int	j;
	int	fd_pipe[2];

	j = 0;
	initialize_pipes(data, fd_pipe, &j);
}
