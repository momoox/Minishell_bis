/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:47:43 by oliove            #+#    #+#             */
/*   Updated: 2023/11/09 23:44:51 by oliove           ###   ########.fr       */
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
#include "minishell.h"

static int	ft_pipe2(t_exec *ex, int *fd_stdin, int *fd_stdout)
{
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
    printf("ft_pipe2 :\n"); 
	if (ex->stdin_st && ex->stdin_st->token != PIPE){
        
		*fd_stdin = file_o(ex->stdin_st->content, ex->stdin_st->token); //data->exec->cmd[0], 0);
    }
	if (*fd_stdin == -1)
		cmd1 = 0;
	if(ex->stdout_st && ex->stdout_st->token != PIPE){
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
 
void ft_pipe(t_data *data, t_mall *mall)
{
    int j;
    int fd_pipe[2];
    pid_t pid;

    
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
        ft_pipe2(&data->exec[j],&data->exec[j + 1].fd_in, &data->exec[j].fd_out);
        pid = fork();
        if (pid == -1)
            exit(EXIT_FAILURE);
         
        if (pid == 0) 
        {
            exec_build(data, mall, data->exec[j].cmd);
            data->exec[j].cmd[0] = ft_path_dir(mall, data->exec[j].cmd[0], ft_my_var(data, "PATH"), -1);
            dup2(data->exec[j].fd_out, STDOUT_FILENO);
            dup2(data->exec[j].fd_in, STDIN_FILENO);
            if (data->exec[j].fd_out != STDOUT_FILENO)
                close(data->exec[j].fd_out);
            if (data->exec[j].fd_in != STDIN_FILENO)
                close(data->exec[j].fd_in); 
            

            execve(data->exec[j].cmd[0], data->exec[j].cmd, data->env);
            perror("execve a échoué ft_pipex i == 0\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            if (data->exec[j].fd_in != STDIN_FILENO)
                close(data->exec[j].fd_in);
            if (data->exec[j].fd_out != STDOUT_FILENO)
                close(data->exec[j].fd_out);
            wait(NULL);
        }
        j++;
    }
    print_debug(data);
}

int	exec_build(t_data *data, t_mall *mall, char **cmd)
{
	int	ret;
	printf("exec_build_for_debug\n");
   	printf("exec_b : cmd [0] == %s\n",*cmd);

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ret = ft_cd2(data, mall, cmd);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0){
       	printf("exec_build_echo\n");
		ret = ft_echo(cmd);
    }
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ret = ft_env(data->env);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ret = ft_export(data,mall, cmd);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ret = ft_pwd();
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ret = ft_unset(data, mall, cmd);
	// else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		// ret = ft_exit(data, cmd->cmd);
	return (ret);
}

void	run_exec(t_data *data, t_mall *mall)
{
    // print_bulding(data,"PATH");
    // print_env_sort(data->env, mall);
    // ft_export()
    init_data_shell(data, mall);
    print_var_build(data);
    // init_env(data,data->env);
    // init_wds(data);
	ft_pipe(data, mall);
}
