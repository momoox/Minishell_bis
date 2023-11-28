/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nouvell_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:23:31 by oliove            #+#    #+#             */
/*   Updated: 2023/11/28 03:41:40 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

// Partie 1 : Initialisation
int	 initialize_pipes(t_data *data, int fd_pipe[2], int *j)
{
	//printf("in initialize_pipes\n");
	while ((*j) < data->nb_exec)
	{
		if (*j < data->nb_exec - 1)
		{
			if (pipe(fd_pipe) == -1)
				exit(EXIT_FAILURE);
			data->exec[*j + 1].fd_in = fd_pipe[0];
			data->exec[*j].fd_out = fd_pipe[1];
			// printf("pipe[0] = %d | [1] = %d\n", fd_pipe[0], fd_pipe[1]);
		}
		else
			data->exec[*j].fd_out = dup(STDOUT_FILENO);
		if (*j == 0)
			data->exec[*j].fd_in = dup(STDIN_FILENO);
		// printf("1: in = %d | out = %d\n", data->exec[*j].fd_in, data->exec[*j].fd_out);
		ft_pipe2(&data->exec[*j], &data->exec[*j].fd_in,
			&data->exec[*j].fd_out);
		if(data->nb_exec > 1){
			
			data->pid = fork();
			if (data->pid == -1)
				exit(EXIT_FAILURE);
			if (data->pid == 0)
			{
				// printf("2: in = %d | out = %d\n", data->exec[*j].fd_in, data->exec[*j].fd_out);
				pipe_execution(data, j);
				exit(EXIT_SUCCESS); // Sortir du loop si c'est le processus enfant
			}
			else {
				cleanup_pipes(data, j);
			}
		}
		// else{
		// 	execute_command(data, &data->exec[*j]);
		// }
  		(*j)++;
	}
	return(1);
	//printf("end initialize_pipes\n");
}



// Partie 2 : Gestion des tubes
int	pipe_execution(t_data *data, int *j)
{
	//printf("in pipe_exec\n");
	int ret;
    if(is_build(data->exec[*j].cmd) == false){
		data->exec[*j].cmd[0] = ft_path_dir(data->mall, data->exec[*j].cmd[0],
			ft_my_var(data, "PATH"), -1);
    }
	// printf("data_exec == [%s]\n",data->exec[*j].cmd[0]);
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
	waitpid(-1,&status,0);
}

// Fonction principale ft_pipe
void	ft_pipe(t_data *data)
{
	// printf("in ft_pipe nb_exec = %d\n", data->nb_exec);
	int		j;
	int		fd_pipe[2];

	j = 0;
	initialize_pipes(data, fd_pipe, &j);

}
