/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:47:43 by oliove            #+#    #+#             */
/*   Updated: 2023/11/27 20:08:22 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// /*
// on recois noeud par noeud :
// 	- data->exec->content
// 	- data->exec->token
// 	- data->env
// les data que jai bessoin dans la struct
// */

#include "util_exec.h"
// #include "minishell.h"

int	ft_pipe2(t_exec *ex, int *fd_stdin, int *fd_stdout)
{
	//printf("in ft_pipe2\n");
	int	cmd1;
	int	i;
	int	fd[2];
	
  
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
    //printf("ft_pipe2 :\n"); 
	if (ex->stdin_st && ex->stdin_st->token == REDIR_I){
        
		*fd_stdin = file_o(ex->stdin_st->content, ex->stdin_st->token); //data->exec->cmd[0], 0);
    }
	if (*fd_stdin == -1)
		cmd1 = 0;
	if(ex->stdout_st && (ex->stdout_st->token == REDIR_O || ex->stdout_st->token == REDIR_A)){
		*fd_stdout = file_o(ex->stdout_st->content, ex->stdout_st->token);//  data->exec->cmd[0], 1);
    }
    //printf("After_check\n");
	// //printf("cmd == [%s] \n",ex->cmd[0]);
	if (!cmd1)
	{
		i++;
		pipe(fd);
        close(fd[1]);
		fd_stdin = &fd[0];
	}
	//printf("end ft_pipe2\n");
	return (i);
}


int ft_lstsize(t_list *list)
{
    int i;

    i = 0;
    while (list)
    {
        i++;
        list = list->next;
    }
    return (i);
}
 
// void ft_pipe(t_data *data, t_mall *mall)
// {
//     int j;
//     int fd_pipe[2];
//     pid_t pid;

    
//     j = 0;
//     while (j < data->nb_exec)
//     {
        
//         if (j < data->nb_exec - 1)
//         {
//             if (pipe(fd_pipe) == -1)
//                 exit(0);
//             data->exec[j + 1].fd_in = fd_pipe[0];
//             data->exec[j].fd_out = fd_pipe[1];
//         }
//         else
//             data->exec[j].fd_out = STDOUT_FILENO;
//         if (j == 0)
//             data->exec[j].fd_in = STDIN_FILENO;
//         ft_pipe2(&data->exec[j],&data->exec[j + 1].fd_in, &data->exec[j].fd_out);
//         exec_build(data, mall, data->exec[j].cmd);
//         pid = fork();
//         if (pid == -1)
//             exit(EXIT_FAILURE);
         
//         if (pid == 0) 
//         {
//             data->exec[j].cmd[0] = ft_path_dir(mall, data->exec[j].cmd[0], ft_my_var(data, "PATH"), -1);
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


int	execute_sys_bin(t_data *data, t_exec *cmd)
{
	//printf("start execute_sys_bin \n");
	if (!cmd->cmd || cmd->cmd[0] == NULL)//'\0')
		return (CMD_NOT_FOUND);
	cmd->path = ft_path_dir(data->mall, *cmd->cmd, ft_my_var(data,"PATH"),0);
	//printf("path = [%s]\n",cmd->path);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->cmd, data->env) == -1)
		errmsg_cmd(data, "execve", NULL, strerror(errno), errno);
	//printf("end execute_sys_bin \n");
	return (EXIT_FAILURE);
}

void	run_exec(t_data *data)
{
	//printf("start run exec\n");
    // print_bulding(data,"PATH");
    // print_env_sort(data->env, data->mall);
    // ft_export()
    init_data_shell(data);
    print_var_build(data);
    init_env(data,data->env);
    init_wds(data);
	//printf("in run %d\n", data->nb_exec);
	// print_debug(data);
	//printf("nb_exec = [%d]\n",data->nb_exec);
	// if(data->nb_exec > 1)
		ft_pipe(data);
	// else{
	// 	//printf("else\n");
	// 	// if(is_build(data->exec->cmd))
	// 		execute_sys_bin(data, data->exec);
	// }
		
	//printf("end run exec\n");
}
int	execute_local_bin(t_data *data, t_exec *cmd)
{
	int	ret;

	ret = check_cmd_not_found(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->cmd[0], cmd->cmd, data->env) == -1)
		return (errmsg_cmd(data, "execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}
int	execute_command(t_data *data, t_exec *cmd)
{
	int	ret;

	if (!cmd || !cmd->cmd)
		exit_shell(data, errmsg_cmd(data, "child", NULL,
				"parsing error: no cmd to execute!", EXIT_FAILURE));
	if (ft_strchr(cmd->cmd[0], '/') == NULL)
	{
		ret = exec_build(data, cmd->cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(data, ret);
		ret = execute_sys_bin(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(data, ret);
	}
	ret = execute_local_bin(data, cmd);
	exit_shell(data, ret);
	return (ret);
}
/// /////////////////test////////////////////////////////////////////////
// void run_exec(t_data *data) {
//     // ... (autre code)

//     if (is_build(data->exec[j].cmd)) {
//         int ret =  run_builtin(data, data->exec[j].cmd);
//         if (ret == CMD_NOT_FOUND) {
//             // La commande n'est pas une fonction intégrée
//             // Traitez-la en conséquence
//             // ...
//         } else if (ret != 0) {
//             // Gestion de l'échec de l'exécution de la fonction intégrée
//             // ...
//         }
//     } else {
//         // La commande n'est pas une fonction intégrée
//         // Traitez-la en conséquence
//         // ...
//     }

//     // ... (autre code)
// }
/////////////////////////////////////////////////////////////