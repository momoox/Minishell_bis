/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:14:52 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 20:02:54 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

int	search_idx(char **env, char *key_str)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], key_str, ft_strlen(key_str)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_my_var(t_data *data, char *str)
{
	int		i;
	char	*var;

	i = 0;
	var = ft_calloc_env(data, 1, ft_strlen(str) + 2);
	ft_strcpy(var, str);
	ft_strcat(var, "=");
	while (data->env && data->env[i])
	{
		if (ft_strncmp(data->env[i], var, ft_strlen(var)) == 0)
			break ;
		i++;
	}
	return (data->env[i]);
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
// 	//printf("val cmd %s\n",cmd[0]);
// 	c_args = ft_split_pipe(cmd[0], ' ');

// 	// //printf("exece : cmd[1] = [%s]\n",cmd[1]);

// 	tmp = ft_strjoin_pipe2(c_args[0], cmd[1]);
// 	c_args[0] = tmp;

// 	//printf("c_args ==  [%s]\n",c_args[0]);
// 	// //printf("exece : tmp == [%s]\n",tmp[0]);
// 	path = ft_path_dir(c_args, ft_my_var(data, "PATH"), -1);
// 	// //printf("var = [%s]\n",ft_my_var(data,cmd));
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
// 	//printf("val cmd %s\n",cmd);
// 	c_args = ft_split_pipe(cmd, ' ');
// 	path = ft_path_dir(c_args, ft_my_var(data, "PATH"), -1);
// 	// //printf("var = [%s]\n",ft_my_var(data,cmd));
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
