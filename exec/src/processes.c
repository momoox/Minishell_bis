/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:14:52 by oliove            #+#    #+#             */
/*   Updated: 2023/11/30 10:04:03 by momox            ###   ########.fr       */
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

void	exece(t_data *data, char **cmd, char **env)
{
	char	*path;

	(void)env;
	path = ft_path_dir(data->mall, cmd[0], ft_my_var(data, "PATH"), -1);
	if (path == cmd[0])
	{
		if (data->flag_unlink == 0)
		{
			ft_putstr_fd("Minishell: ", STDERR_FILENO);
			ft_putstr_fd(cmd[0], STDERR_FILENO);
			ft_putstr_fd_jump(": command not found", STDERR_FILENO);
			data->exit_code = 127;
			exit_shell(data, data->exit_code);
		}
	}
	if (execve(cmd[0], cmd, data->env) == -1)
	{
		if (data->flag_unlink == 0)
		{
			ft_putstr_fd("Minishell:1 ", STDERR_FILENO);
			ft_putstr_fd(cmd[0], STDERR_FILENO);
			ft_putstr_fd_jump(": No such file or directory", STDERR_FILENO);
			exit(1);
		}
	}
}
