/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:47:43 by oliove            #+#    #+#             */
/*   Updated: 2023/11/04 21:37:20 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

// /*
// on recois noeud par noeud :
// 	- data->exec->content
// 	- data->exec->token
// 	- data->env
// les data que jai bessoin dans la struct
// */
// #include "util_exec.h"
// #include "minishell.h"

static int	ft_pipe2(t_exec *ex, int *fd_stdin, int *fd_stdout)
{
	int	cmd1;
	int	i;
	int	fd[2];
	
  
//    ex->fd_in;
//    ex->fd_out;
//    ex->stdin_st;
//    ex->stdout_st;
   /*
	Bleu \033[0;34m
	Noir \033[0;30m
	Rouge \033[0;31m
	Vert \033[0;32m
	Jaune \033[0;33m
	Violet \033[0;35m
*/ 
	cmd1 = 1;
	i = 0;
    printf("ft_pipe2 :\n"); 
    // printf("data->fd_in[%d] | fd_stdin == [%d] == [%s] | fd_stdout == [%d] | cmd == [%d]\n", ex->fd_in, *fd_stdin,(ex->stdin_st != NULL) ? ex->stdin_st->content : NULL, *fd_stdout ,cmd1);
	if (ex->stdin_st && ex->stdin_st->token != PIPE){
        
        printf("stdin_st \033[0;33m[%s]\033[0m token == \033[0;34m[%d]\033[0m\n",(ex->stdin_st !=NULL) ? ex->stdin_st->content : NULL, (ex->stdin_st !=NULL) ? ex->stdin_st->token : -1);
		*fd_stdin = file_o(ex->stdin_st->content, ex->stdin_st->token); //data->exec->cmd[0], 0);
    }
	if (*fd_stdin == -1)
		cmd1 = 0;
	if(ex->stdout_st && ex->stdout_st->token != PIPE){
        printf("stdout_st \033[0;33m[%s]\033[0m token == \033[0;34m[%d]\033[0m\n",(ex->stdout_st !=NULL) ? ex->stdout_st->content : NULL,(ex->stdout_st !=NULL) ? ex->stdout_st->token : -1);
		*fd_stdout = file_o(ex->stdout_st->content, ex->stdout_st->token);//  data->exec->cmd[0], 1);
    }
    printf("After_check\n");
	if (!cmd1)
	{
		i++;
		pipe(fd);
        close(fd[1]);
		fd_stdin = &fd[0];
	}
	return (i);
}


// int ft_lstsize(t_list *list)
// {
//     int i;

//     i = 0;
//     while (list)
//     {
//         i++;
//         list = list->next;
//     }
//     return (i);
// }
 
void ft_pipe(t_data *data)
{
    int j;
    int fd_pipe[2];
    pid_t pid;

    // printf("exec : %d\n", data->nb_exec);
    j = 0;
    while (j < data->nb_exec)
    {
        
        if (j < data->nb_exec - 1)
        {
            if (pipe(fd_pipe) == -1)
                exit(0);
            data->exec[j + 1].fd_in = fd_pipe[0];
            data->exec[j].fd_out = fd_pipe[1];
        }
        else
            data->exec[j].fd_out = STDOUT_FILENO;
        if (j == 0)
            data->exec[j].fd_in = STDIN_FILENO;
        // printf("in = %d | out = %d\n", data->exec[j].fd_in, data->exec[j].fd_out);

        ft_pipe2(&data->exec[j],&data->exec[j + 1].fd_in, &data->exec[j].fd_out);
        pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
         
//         if (pid == 0) 
//         {
//             // printf("in = %d | out = %d\n", data->exec[j].fd_in, data->exec[j].fd_out);
//             data->exec[j].cmd[0] = ft_path_dir(data->exec[j].cmd[0], ft_my_var(data, "PATH"), -1);
//             //print/////////////////////////////////////////////
//             for (int l = 0; data->exec[j].cmd[l]; l++)
//                 // printf("cmd[%d] = %s\n", l, data->exec[j].cmd[l]);
//                 /////////////////////////////////////////////////
//             dup2(data->exec[j].fd_out, STDOUT_FILENO);
//             dup2(data->exec[j].fd_in, STDIN_FILENO);
//             if (data->exec[j].fd_out != STDOUT_FILENO)
//                 close(data->exec[j].fd_out);
//             if (data->exec[j].fd_in != STDIN_FILENO)
//                 close(data->exec[j].fd_in); 
            
//             execve(data->exec[j].cmd[0], data->exec[j].cmd, data->env);
//             perror("execve a échoué ft_pipex i == 0\n");
//             exit(EXIT_FAILURE);
//         }
//         else
//         {
//             if (data->exec[j].fd_in != STDIN_FILENO)
//                 close(data->exec[j].fd_in);
//             if (data->exec[j].fd_out != STDOUT_FILENO)
//                 close(data->exec[j].fd_out);
//             wait(NULL);
//         }
//         j++;
//     }
//     print_debug(data);
// }


// void	run_exec(t_data *data)
// {

// 	//ft_pipe(data);
	}
}
