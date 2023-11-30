/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:35:32 by oliove            #+#    #+#             */
/*   Updated: 2023/11/30 02:36:24 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

int	execute_sys_bin(t_data *data, t_exec *cmd)
{
	if (!cmd->cmd || cmd->cmd[0] == NULL)
		return (CMD_NOT_FOUND);
	cmd->path = ft_path_dir(data->mall, *cmd->cmd, ft_my_var(data, "PATH"), 0);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	exece(data, *cmd->cmd, data->env);
	// if (execve(cmd->path, cmd->cmd, data->env) == -1)
	// 	errmsg_cmd(data, (char *[3]){"execve", NULL, strerror(errno)}, errno);
	return (EXIT_FAILURE);
}

void	run_exec(t_data *data)
{
	int	t;

	init_data_shell(data);
	init_env(data, data->env);
	init_wds(data);
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
	exece(data, *cmd->cmd, data->env);
	// if (execve(cmd->cmd[0], cmd->cmd, data->env) == -1)
	// 	return (errmsg_cmd(data, (char *[3]){"execve", NULL, strerror(errno)},
			// errno));
	return (EXIT_FAILURE);
}

int	execute_command(t_data *data, t_exec *cmd)
{
	int	ret;

	if (!cmd || !cmd->cmd)
		exit_shell(data, errmsg_cmd(data, (char *[3]){"child", NULL,
				"parsing error: no cmd to execute!"}, EXIT_FAILURE));
	if (ft_strchr(*cmd->cmd, '/') == NULL)
	{
		ret = exec_build(data, cmd->cmd);
		if (ret != CMD_NOT_FOUND && is_forck(data, cmd) == 0)
			exit_shell(data, ret);
		if (!find_builtin(data, cmd->cmd[0]))
		{
			ret = execute_sys_bin(data, cmd);
			if (ret != CMD_NOT_FOUND && is_forck(data, cmd) == 0)
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
