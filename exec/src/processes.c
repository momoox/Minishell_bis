/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:14:52 by oliove            #+#    #+#             */
/*   Updated: 2023/10/22 00:20:47 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

// void	ft_pipe(t_data *data, char *cmd, char **env)
// {
// 	pid_t	pid;
// 	// int		fd_pipe[2];

// 	if (pipe(data->exec->fd_pipe) == -1)
// 		exit(0);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(0);
// 	if (!pid)
// 	{
// 		close(data->exec->fd_pipe[0]);
// 		dup2(data->exec->fd_pipe[1], 1);
// 		exece(data,&cmd, env);
// 	}
// 	else
// 	{
// 		close(data->exec->fd_pipe[1]);
// 		dup2(data->exec->fd_pipe[0], 0);
// 	}
// }

void	free_tab_args(char **args)
{
	char	**pos;

	if (args == NULL)
		return ;
	pos = args;
	while (*pos != NULL)
		free(*(pos++));
	free(args);
}

// char *ft_my_path(t_data *data,char *cmd, char **env)
// {

// 	char	**c_args;
// 	(void)env;
// 	char	*path;
// 	printf("val cmd %s\n",cmd);
// 	c_args = ft_split(cmd, ' ');
// 	printf("val2 env %s\n", data->env[0]);
// 	path = ft_path_dir(c_args, ft_my_var(data, "PATH"), -1);
	
// 	printf("var = [%s]\n",ft_my_var(data,cmd));
// 	return (path);	

// }


char *ft_my_var(t_data *data,char *str)
{
	// t_data tmp;
	// char *tmp;
	int i = 0;
	int size = 0;
	char *var = calloc(1,strlen(str) + 2);
	strcpy(var,str);
	strcat(var,"=");
	while (data->env && data->env[i])
	{
		// printf("prout\n");
		if(strncmp(data->env[i], var, strlen(var)) == 0)
			break;
		i++;	
	}
	size = strlen(var);
	free(var);
	// if (!data->env[i])
		// return( NULL);
	return(data->env[i]+size);
}

// void	exece(t_data *data, char **cmd, char **env)
// {
// 	char	**c_args;
// 	// char	**c_args1;
// 	(void)env;
// 	char	*path;
// 	char 	*tmp;
	
// 	// int		i;
// 	// ft_my_path(data);
// 	// i = -1;
// 	printf("val cmd %s\n",cmd[0]);
// 	c_args = ft_split_pipe(cmd[0], ' ');
	
// 	// printf("exece : cmd[1] = [%s]\n",cmd[1]);
	
// 	tmp = ft_strjoin_pipe2(c_args[0], cmd[1]);
// 	c_args[0] = tmp;
	
	
// 	printf("c_args ==  [%s]\n",c_args[0]);
// 	// printf("exece : tmp == [%s]\n",tmp[0]);
// 	path = ft_path_dir(c_args, ft_my_var(data, "PATH"), -1);
// 	// printf("var = [%s]\n",ft_my_var(data,cmd));
// 	if ((char **)path == c_args)
// 	{
// 		ft_putstr_fd("pipex: ", STDERR_FILENO);
// 		ft_putstr_fd(c_args[0], STDERR_FILENO);
// 		ft_putstr_fd_jump(": command not found", STDERR_FILENO);
// 		free_tab_args(c_args);
// 		exit(0);
// 	}
// 	if (execve(path, c_args, data->env) == -1)
// 	{
// 		ft_putstr_fd("pipex: ", STDERR_FILENO);
// 		ft_putstr_fd(c_args[0], STDERR_FILENO);
// 		ft_putstr_fd_jump(": No such file or directory", STDERR_FILENO);
// 		free_tab_args(c_args);
// 		exit(0);
// 	}
// }
// void	exece(t_data *data, char *cmd, char **env)
// {
// 	char	**c_args;
// 	(void)env;
// 	char	*path;
// 	// int		i;
// 	// ft_my_path(data);
// 	// i = -1;
// 	printf("val cmd %s\n",cmd);
// 	c_args = ft_split_pipe(cmd, ' ');
// 	path = ft_path_dir(c_args, ft_my_var(data, "PATH"), -1);
// 	// printf("var = [%s]\n",ft_my_var(data,cmd));
// 	if ((char **)path == c_args)
// 	{
// 		ft_putstr_fd("pipex: ", STDERR_FILENO);
// 		ft_putstr_fd(c_args[0], STDERR_FILENO);
// 		ft_putstr_fd_jump(": command not found", STDERR_FILENO);
// 		free_tab_args(c_args);
// 		exit(0);
// 	}
// 	if (execve(path, c_args, data->env) == -1)
// 	{
// 		ft_putstr_fd("pipex: ", STDERR_FILENO);
// 		ft_putstr_fd(c_args[0], STDERR_FILENO);
// 		ft_putstr_fd_jump(": No such file or directory", STDERR_FILENO);
// 		free_tab_args(c_args);
// 		exit(0);
// 	}
// }
