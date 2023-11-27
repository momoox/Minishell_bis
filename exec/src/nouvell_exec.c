/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nouvell_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:23:31 by oliove            #+#    #+#             */
/*   Updated: 2023/11/27 02:15:16 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

// Partie 1 : Initialisation
// void	initialize_pipes(t_data *data, int fd_pipe[2], int *j)
// {
// 	//printf("in initialize_pipes\n");
//     //printf("*j = %d\n", *j);
//     //printf("nb_exec = %d\n", data->nb_exec);

	
// 	while ((*j) < data->nb_exec)
// 	{
//         //printf("in while init_pipe");   
// 		if (*j < data->nb_exec - 1)
// 		{
// 			if (pipe(fd_pipe) == -1)
// 				exit(EXIT_FAILURE);
// 			data->exec[*j + 1].fd_in = fd_pipe[0];
// 			data->exec[*j].fd_out = fd_pipe[1];
// 		}
// 		else
// 			data->exec[*j].fd_out = STDOUT_FILENO;
// 		if (*j == 0)
// 			data->exec[*j].fd_in = STDIN_FILENO;
// 		ft_pipe2(&data->exec[*j], &data->exec[*j + 1].fd_in,
// 			&data->exec[*j].fd_out);
// 		data->pid = fork();
// 		//printf("pid == [%d]\n",data->pid);
// 		if (data->pid == -1)
// 			exit(EXIT_FAILURE);
// 		if (data->pid == 0)
// 		{
//   		    (*j)++;
// 			break ; // Sortir du loop si c'est le processus enfant
// 		}
		
// 	}
// 	//printf("end initialize_pipes\n");
// }
void initialize_pipes(t_data *data, int fd_pipe[2], int *j)
{
    //printf("in initialize_pipes\n");
    //printf("*j = %d\n", *j);
    //printf("nb_exec = %d\n", data->nb_exec);

    while ((*j) < data->nb_exec)
    {
        //printf("in while init_pipe\n");

        if (*j < data->nb_exec - 1)
        {
            if (pipe(fd_pipe) == -1)
                exit(EXIT_FAILURE);

            data->exec[*j + 1].fd_in = fd_pipe[0];
            data->exec[*j].fd_out = fd_pipe[1];
        }
        else
        {
            data->exec[*j].fd_out = STDOUT_FILENO;
        }

        if (*j == 0)
        {
            data->exec[*j].fd_in = STDIN_FILENO;
        }

        ft_pipe2(&data->exec[*j], &data->exec[*j + 1].fd_in, &data->exec[*j].fd_out);
        data->pid = fork();

        //printf("pid == [%d]\n", data->pid);

        if (data->pid == -1)
            exit(EXIT_FAILURE);

        if (data->pid == 0)
        {
            // Sortir du loop si c'est le processus enfant
            break;
        }

        // Incrementer j ici pour le processus parent
        (*j)++;
    }

    //printf("end initialize_pipes\n");
}


// Partie 2 : Gestion des tubes
void	pipe_execution(t_data *data, int *j)
{
	//printf("in pipe_exec\n");
	int ret;
    // if (is_build(data->exec[*j].cmd) == true)
        // exec_build(data, data->exec[*j].cmd);
    // else
	// //printf("\033[0;33m%s\033[0m data_exec[*j].cmd[o]\n",data->exec[*j].cmd[0]);
	// if (is_build(data->exec[*j].cmd) == true)
    //    ret = exec_build(data, data->exec[*j].cmd);
    // else
	// //printf("pipe_exec\ndata->exec[*j].cmd = [%s]\n",data->exec[*j].cmd[0]);
	//printf("\033[0;31mbefore is_build\033[0m\n");
    if(is_build(data->exec[*j].cmd) == false){
		//printf("data->exe\033[0;31m[%d]\033[0m.cmd[0] = \033[0;33m%s\033[0m\nIsbuild = \033[0;31m[%d]\033[0m\n",*j,data->exec[*j].cmd[0],is_build(data->exec[*j].cmd));
		data->exec[*j].cmd[0] = ft_path_dir(data->mall, data->exec[*j].cmd[0],
			ft_my_var(data, "PATH"), -1);
    }
	
    dup2(data->exec[*j].fd_out, STDOUT_FILENO);
	dup2(data->exec[*j].fd_in, STDIN_FILENO);
	if (data->exec[*j].fd_out != STDOUT_FILENO)
		close(data->exec[*j].fd_out);
	if (data->exec[*j].fd_in != STDIN_FILENO)
		close(data->exec[*j].fd_in);
	if (exec_build(data,  data->exec[*j].cmd) == CMD_NOT_FOUND ) //j'ai modifié (momo)
	{
			
		if(execve(data->exec[*j].cmd[0], data->exec[*j].cmd, data->env) == -1)
		{
			//printf("execve error cmd = [%s]\n",data->exec[*j].cmd[0]);
			perror("execve a échoué ft_pipex i == 0\n");
			exit(EXIT_FAILURE);
		}
	}
	//printf("end pipe_exec\n");
}

// Partie 3 : Nettoyage
void	cleanup_pipes(t_data *data, int *j)
{
	//printf("in cleanup_pipes\n");
	if (*j == 0)
		data->exec[*j].fd_in = STDIN_FILENO;
	if (data->exec[*j].fd_in != STDIN_FILENO)
		close(data->exec[*j].fd_in);
	if (data->exec[*j].fd_out != STDOUT_FILENO)
		close(data->exec[*j].fd_out);
	wait(NULL);
	(*j)++;
	//printf("end cleanup_pipes\n");
}

// Fonction principale ft_pipe
void	ft_pipe(t_data *data)
{
	//printf("in ft_pipe\n");
	int		j;
	int		fd_pipe[2];

	j = 0;
	initialize_pipes(data, fd_pipe, &j);
	while (j < data->nb_exec)
	{
		// print_debug(data);
		if (data->pid == 0)
			pipe_execution(data, &j);
		else
			cleanup_pipes(data, &j);
		
	}
	//printf("end ft_pipe\n");
	
	// print_debug(data);
}
