/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:47:43 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 18:11:01 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "util_exec.h"
#include "minishell.h"

int	ft_pipe2(t_exec *ex, int *fd_stdin, int *fd_stdout)
{
	int	cmd1;
	int	i;
	int	fd[2];

	cmd1 = 1;
	i = 0;
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

int	execute_sys_bin(t_data *data, t_exec *cmd)
{
	if (!cmd->cmd || cmd->cmd[0] == NULL)//'\0')
		return (CMD_NOT_FOUND);
	cmd->path = ft_path_dir(data->mall, *cmd->cmd, ft_my_var(data,"PATH"),0);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->cmd, data->env) == -1)
		errmsg_cmd(data, (char *[3]){"execve", NULL, strerror(errno)}, errno);
	return (EXIT_FAILURE);
}

void	run_exec(t_data *data)
{
	
    init_data_shell(data);
    init_env(data,data->env);
	init_wds(data);
	int t;
	
	t = is_forck(data, data->exec);	
	if (data->nb_exec > 1 || is_forck(data, data->exec) == 0)
		ft_pipe(data);
	else
		execute_command(data, &data->exec[0]);
	
}
int	execute_local_bin(t_data *data, t_exec *cmd)
{
	int	ret;

	ret = check_cmd_not_found(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->cmd[0], cmd->cmd, data->env) == -1)
		return (errmsg_cmd(data, (char *[3]){"execve", NULL, strerror(errno)}, errno));
	return (EXIT_FAILURE);
}
int	execute_command(t_data *data, t_exec *cmd)
{
	int	ret;

	if (!cmd || !cmd->cmd)
		exit_shell(data, errmsg_cmd(data, (char *[3]){"child", NULL,
				"parsing error: no cmd to execute!"}, EXIT_FAILURE));
	if (/* check_path_slash(ft_my_var(data,"PATH"), cmd->cmd[0]) */ft_strchr(*cmd->cmd, '/') == NULL)
	{
		ret = exec_build(data, cmd->cmd);
		printf("ret1 == [%d], is_fork = %d\n", ret, is_forck(data, cmd));
		if (ret != CMD_NOT_FOUND && is_forck(data, cmd) == 0/*  && ret != EXIT_SUCCESS */)
			exit_shell(data, ret);
		if(!find_builtin(cmd->cmd[0], data->func))
		{
			ret = execute_sys_bin(data, cmd);
			if (ret != CMD_NOT_FOUND && is_forck(data, cmd) == 0/* && ret != EXIT_SUCCESS */)
				exit_shell(data, ret);
		}
	}
	else
	{
		ret = execute_local_bin(data, cmd);
		exit_shell(data, ret);
	}
	return (ret);
}

int is_forck(t_data *data, t_exec *cmd)
{
	
	builtin_func func = find_builtin(cmd->cmd[0], data->func);
	if (func != NULL){
		if(ft_strncmp(cmd->cmd[0], "export", 7) == 0 && cmd->cmd[1] == NULL)
			return (0);	
		else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
			return (0);	
		else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
			return (0);	
		return (1);
	}
	return (0);
}

