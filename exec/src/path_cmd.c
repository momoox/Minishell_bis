/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:54:40 by oliove            #+#    #+#             */
/*   Updated: 2023/11/04 21:37:55 by momox            ###   ########.fr       */
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


void	*ft_path_dir(char *cmd, char *path, int i)
{
	char	**path_directo;
	char	*name;
	char	*tmp;
	// printf("ft_path_dir : cmd == [%s]\n",cmd);
	if (check_path_slash(path, cmd) == 0)
		return (cmd);
	path_directo = ft_split(path, ':');
	while (path_directo[++i] != NULL)
	{
		tmp = ft_strjoin_pipe(path_directo[i], "/");
		name = ft_strjoin_pipe(tmp, cmd);
		free(tmp);
		if (access(name, F_OK) == 0)
		{
			i = 0;
			while (path_directo[i])
				free(path_directo[i++]);
			free(cmd);
			return (name);
		}
		// printf("ft_path_dir : name = [%s]\n",name);
		// printf("ft_path_dir : cmd = [%s]\n",cmd);
		free(name);
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
