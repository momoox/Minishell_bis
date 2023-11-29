/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nouvell_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:23:31 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 03:52:43 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

// Partie 1 : Initialisation
int	 initialize_pipes(t_data *data, int fd_pipe[2], int *j)
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
			data->pid = fork();
			if (data->pid == -1)
				exit(EXIT_FAILURE);
			if (data->pid == 0)
			{
				pipe_execution(data, j);
				exit(EXIT_SUCCESS); // Sortir du loop si c'est le processus enfant
			}
			else {
				cleanup_pipes(data, j);
			}
  		(*j)++;
	}
	return(1);
}

// Partie 2 : Gestion des tubes
int	pipe_execution(t_data *data, int *j)
{
	printf("in pipe_exec j = %d pid = %d | ppid = %d\n",*j,getpid(),getppid());
	int ret;
	// find_builtin(data->exec[*j].cmd[0], t_b *builtins)
	builtin_func func = find_builtin(data->exec[*j].cmd[0], builtins);
    if(/* is_build(data->exec[*j].cmd) == false *//* find_builtin(data->exec[*j].cmd[0], data->func) == NULL */func == NULL){
		data->exec[*j].cmd[0] = ft_path_dir(data->mall, data->exec[*j].cmd[0],
			ft_my_var(data, "PATH"), -1);
    }
    dup2(data->exec[*j].fd_out, STDOUT_FILENO);
	dup2(data->exec[*j].fd_in, STDIN_FILENO);
	close(data->exec[*j].fd_out);
	close(data->exec[*j].fd_in);
	ret = execute_command(data, &data->exec[*j]);
	return (ret);
}

// Partie 3 : Nettoyage
void	cleanup_pipes(t_data *data, int *j)
{
	int status;
	status = close(data->exec[*j].fd_in);
	status = close(data->exec[*j].fd_out);
	waitpid(-1, &status, 0);
}

// Fonction principale ft_pipe
void	ft_pipe(t_data *data)
{
	int		j;
	int		fd_pipe[2];

	j = 0;
	initialize_pipes(data, fd_pipe, &j);

}
