/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:54:40 by oliove            #+#    #+#             */
/*   Updated: 2023/11/30 19:07:49 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

int	check_path_slash(char *path, char *cmd)
{
	if (!cmd)
		return (-1);
	if (path == NULL || cmd[0] == '/' || (ft_strlen(cmd) >= 2 && cmd[0] == '.'
			&& cmd[1] == '/') || (ft_strlen(cmd) >= 3 && cmd[0] == '.'
			&& cmd[1] == '.' && cmd[2] == '/'))
		return (0);
	return (-1);
}

void	*ft_path_dir(t_mall *mall, char *cmd, char *path, int i)
{
	char	**path_directo;
	char	*name;
	char	*tmp;

	if (check_path_slash(path, cmd) == 0)
		return (cmd);
	path_directo = ft_split(mall, path, ':');
	while (path_directo[++i] != NULL)
	{
		tmp = ft_strjoin_pipe(mall, path_directo[i], "/");
		name = ft_strjoin_pipe(mall, tmp, cmd);
		if (access(name, F_OK) == 0)
		{
			i = 0;
			while (path_directo[i++])
				;
			return (name);
		}
	}
	return (cmd);
}

int	file_o(char *file, int token)
{
	int	res;

	if (token == REDIR_I)
		res = open(file, O_RDONLY);
	if (token == REDIR_O)
		res = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (token == REDIR_A)
		res = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (res == -1)
		return (-1);
	return (res);
}

int	init_env(t_data *data, char **env)
{
	int	i;

	data->env = ft_calloc_env(data, env_var_count(env) + 1,
			sizeof (*data->env));
	if (!data->env)
		return (EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		data->env[i] = ft_strdup_pipe(data, env[i]);
		if (!data->env[i])
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_wds(t_data *data)
{
	char	buff[PATH_MAX];
	char	*wd;

	wd = getcwd(buff, PATH_MAX);
	data->shell->cwd = ft_strdup_pipe(data, wd);
	if (!data->shell->cwd)
		return (0);
	if (get_env_var_index(data, data->env, "OLDPWD") != -1)
	{
		data->shell->old_pwd = ft_strdup(data, get_env_var_value(data,
					data->env, "OLDPWD"));
		if (!data->shell->old_pwd)
			return (0);
	}
	else
	{
		data->shell->old_pwd = ft_strdup(data, wd);
		if (!data->shell->old_pwd)
			return (0);
	}
	return (1);
}
