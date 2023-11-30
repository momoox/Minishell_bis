/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 03:41:21 by oliove            #+#    #+#             */
/*   Updated: 2023/11/30 10:01:57 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*i;

	i = (unsigned char *)s;
	while (n > 0)
	{
		*i++ = '\0';
		n--;
	}
}

void	*ft_calloc_env(t_data *data, size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc_plus_plus(&data->mall, count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	**realloc_env(t_data *data, size_t size)
{
	char	**new_env;
	size_t	i;

	new_env = ft_calloc_env(data, size + 1, sizeof(*new_env));
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(data, data->env[i]);
		i++;
	}
	return (new_env);
}

bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

int	check_cmd_not_found(t_data *data, t_exec *cmd)
{
	if (ft_strchr(cmd->cmd[0], '/') == NULL && get_env_var_index(data,
			data->env, "PATH") != -1)
		return (errmsg_cmd(data, (char *[3]){cmd->cmd[0], NULL,
				"command not found"}, CMD_NOT_FOUND));
	if (access(cmd->cmd[0], F_OK) != 0)
		return (errmsg_cmd(data, (char *[3]){cmd->cmd[0], NULL,
				strerror(errno)}, CMD_NOT_FOUND));
	else if (cmd_is_dir(cmd->cmd[0]))
		return (errmsg_cmd(data, (char *[3]){cmd->cmd[0], NULL,
				"is a directory"}, CMD_NOT_EXECUTABLE));
	else if (access(cmd->cmd[0], F_OK | X_OK) != 0)
		return (errmsg_cmd(data, (char *[3]){cmd->cmd[0], NULL,
				strerror(errno)}, CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
