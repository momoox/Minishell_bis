/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nouvell_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:23:31 by oliove            #+#    #+#             */
/*   Updated: 2023/11/22 20:27:53 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

// Partie 1 : Initialisation
void	initialize_pipes(t_data *data, int fd_pipe[2], pid_t *pid)
{
	int	j;

	j = 0;
	while (j < data->nb_exec)
	{
		if (j < data->nb_exec - 1)
		{
			if (pipe(fd_pipe) == -1)
				exit(EXIT_FAILURE);
			data->exec[j + 1].fd_in = fd_pipe[0];
			data->exec[j].fd_out = fd_pipe[1];
		}
		else
			data->exec[j].fd_out = STDOUT_FILENO;
		if (j == 0)
			data->exec[j].fd_in = STDIN_FILENO;
		ft_pipe2(&data->exec[j], &data->exec[j + 1].fd_in,
			&data->exec[j].fd_out);
		// exec_build(data, mall, data->exec[*j].cmd);
		*pid = fork();
		if (*pid == -1)
			exit(EXIT_FAILURE);
		if (*pid == 0)
			break ; // Sortir du loop si c'est le processus enfant
		j++;
	}
}

// Partie 2 : Gestion des tubes
void	pipe_execution(t_data *data, int *j)
{
	data->exec[*j].cmd[0] = ft_path_dir(data->mall, data->exec[*j].cmd[0],
		ft_my_var(data, "PATH"), -1);
	dup2(data->exec[*j].fd_out, STDOUT_FILENO);
	dup2(data->exec[*j].fd_in, STDIN_FILENO);
	if (data->exec[*j].fd_out != STDOUT_FILENO)
		close(data->exec[*j].fd_out);
	if (data->exec[*j].fd_in != STDIN_FILENO)
		close(data->exec[*j].fd_in);
	execve(data->exec[*j].cmd[0], data->exec[*j].cmd, data->env);
	perror("execve a échoué ft_pipex i == 0\n");
	exit(EXIT_FAILURE);
}

// Partie 3 : Nettoyage
void	cleanup_pipes(t_data *data, int *j)
{
	if (*j == 0)
		data->exec[*j].fd_in = STDIN_FILENO;
	if (data->exec[*j].fd_in != STDIN_FILENO)
		close(data->exec[*j].fd_in);
	if (data->exec[*j].fd_out != STDOUT_FILENO)
		close(data->exec[*j].fd_out);
	wait(NULL);
	(*j)++;
}

// Fonction principale ft_pipe
void	ft_pipe(t_data *data)
{
	int		j;
	int		fd_pipe[2];
	pid_t	pid;

	j = 0;
	initialize_pipes(data, fd_pipe, &pid);
	while (j < data->nb_exec)
	{
		if (pid == 0)
		{
			pipe_execution(data, &j);
		}
		else
		{
			cleanup_pipes(data, &j);
		}
	}
	print_debug(data);
}
