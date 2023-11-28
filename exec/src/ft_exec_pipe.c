/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:47:43 by oliove            #+#    #+#             */
/*   Updated: 2023/11/28 04:35:19 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "util_exec.h"

int	ft_pipe2(t_exec *ex, int *fd_stdin, int *fd_stdout)
{
	int	cmd1;
	int	i;
	int	fd[2];

	cmd1 = 1;
	i = 0;
	// if (ex->stdin_st)
	// 	printf("in = %s | token = %d\n", ex->stdin_st->content, ex->stdin_st->token);
	// if (ex->stdout_st)
	// 	printf("out = %s | token = %d\n", ex->stdout_st->content, ex->stdout_st->token);
	if (ex->stdin_st && ex->stdin_st->token == REDIR_I){
        close(*fd_stdin);
		*fd_stdin = file_o(ex->stdin_st->content, ex->stdin_st->token); //data->exec->cmd[0], 0);
    }
	if (*fd_stdin == -1)
		cmd1 = 0;
	if(ex->stdout_st && (ex->stdout_st->token == REDIR_O || ex->stdout_st->token == REDIR_A)){
        close(*fd_stdout);
		*fd_stdout = file_o(ex->stdout_st->content, ex->stdout_st->token);//  data->exec->cmd[0], 1);
    }
	if (!cmd1)
	{
		i++;
		pipe(fd);
        close(fd[1]);
		*fd_stdin = fd[0];
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
// int	prep_exec(t_data *data, int *fd_pipe, int *j)
// {
// 	// printf("pre_exec %p \n",data->exec);
// 	if (!data || !data->exec)
// 		return (EXIT_SUCCESS);
// 	// printf("pre_exec2\n");
// 	if (!data->exec[*j].cmd[0])
// 	{
// 		// printf("pre exec val cmd {%s}\n", data->exec[*j].cmd[0]);
// 		if (data->exec
// 			&& !initialize_pipes(data, fd_pipe, j))
// 			return (EXIT_FAILURE);
// 		return (EXIT_SUCCESS);
// 	}
// 	return (CMD_NOT_FOUND);
// }
int	execute_sys_bin(t_data *data, t_exec *cmd)
{
	if (!cmd->cmd || cmd->cmd[0] == NULL)//'\0')
		return (CMD_NOT_FOUND);
	cmd->path = ft_path_dir(data->mall, *cmd->cmd, ft_my_var(data,"PATH"),0);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->cmd, data->env) == -1)
		errmsg_cmd(data, "execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

void	run_exec(t_data *data)
{
	//printf("start run exec\n");
    // print_bulding(data,"PATH");
    // print_env_sort(data->env, data->mall);
    // ft_export()
    init_data_shell(data);
    // print_var_build(data);
    init_env(data,data->env);
	// for(int i = 0; data->env[i]; i++){
	// 	printf("%s\n",data->env[i]);
	// }
    init_wds(data);
	// prep_exec(data);
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
	if (/* check_path_slash(ft_my_var(data,"PATH"), cmd->cmd[0]) */ft_strchr(*cmd->cmd, '/') == NULL)
	{
		// printf("execute_command[0]== [%s]\n", data->exec[0].cmd[0]);
		
		ret = exec_build(data, cmd->cmd);
		printf("ret1 == [%d]\n", ret);
		if (ret != CMD_NOT_FOUND && ret != EXIT_SUCCESS)
			exit_shell(data, ret);
		if(!find_builtin(cmd->cmd[0], data->func))
		{
			ret = execute_sys_bin(data, cmd);
			printf("ret2 == [%d]\n", ret);
			
			if (ret != CMD_NOT_FOUND && ret != EXIT_SUCCESS)
				exit_shell(data, ret);
		}
		
	}
	else
	{
		ret = execute_local_bin(data, cmd);
		// printf("ret3 == [%d]\n", ret);
		exit_shell(data, ret);
	}
	return (ret);
}
