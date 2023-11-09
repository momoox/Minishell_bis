/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:54:40 by oliove            #+#    #+#             */
/*   Updated: 2023/11/09 23:40:14 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

int	check_path_slash(char *path, char *cmd)
{
	if (!cmd)
		return -1;
	if (path == NULL || cmd[0] == '/' || (ft_strlen(cmd) >= 2
			&& cmd[0] == '.' && cmd[1] == '/') || (ft_strlen(cmd) >= 3
			&& cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
		return (0);
	return (-1);
}


void	*ft_path_dir(t_mall *mall, char *cmd, char *path, int i)
{
	char	**path_directo;
	char	*name;
	char	*tmp;
	// printf("ft_path_dir : cmd == [%s]\n",cmd);
	if (check_path_slash(path, cmd) == 0)
		return (cmd);
	path_directo = ft_split(mall, path, ':');
	while (path_directo[++i] != NULL)
	{
		tmp = ft_strjoin_pipe(mall, path_directo[i], "/");
		name = ft_strjoin_pipe(mall, tmp, cmd);
		//free(tmp);
		if (access(name, F_OK) == 0)
		{
			i = 0;
			while (path_directo[i])
				//free(path_directo[i++]);
			//free(cmd);
			return (name);
		}
		// printf("ft_path_dir : name = [%s]\n",name);
		// printf("ft_path_dir : cmd = [%s]\n",cmd);
		//free(name);
	}
	return (cmd);
}

int	file_o(char *file, int token)
{
	int	res;

	// pour redir_in
	if (token == REDIR_IN)
		res = open(file, O_RDONLY, 0777);
	// for redir_out
	if (token == REDIR_OUT)
		res = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// redir_Append
	if (token == REDIR_APPEND)
		res = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (res == -1)
		return (-1);
	return (res);
}
int	init_env(t_data *data, t_mall *mall, char **env)
{
	int		i;

	data->env = ft_calloc_env(mall, env_var_count(env) + 1, sizeof * data->env);
	if (!data->env)
		return (0);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup_pipe(mall, env[i]);
		if (!data->env[i])
			return (0);
		i++;
	}
	return (1);
}

int	init_wds(t_data *data, t_mall *mall)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->shell->cwd = ft_strdup_pipe(mall, wd);
	if (!data->shell->cwd)
	{
		return (0);
	}
	if (get_env_var_index(mall, data->env, "OLDPWD") != -1)
	{
		data->shell->hold_pwd = ft_strdup(mall, get_env_var_value(mall, data->env,
					"OLDPWD"));
		if (!data->shell->hold_pwd){
			
			//free(wd);
			return (0);
		}
	}
	else
	{
		data->shell->hold_pwd = ft_strdup(mall,wd);
		if (!data->shell->hold_pwd)
		{
			//free(wd);	
			return (0);
		}
	}
	return (1);
}

