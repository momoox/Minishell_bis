/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:11:03 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 04:50:57 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

void	p_error_perm(char *av)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(av, STDERR_FILENO);
	ft_putstr_fd_jump(": Permission denied", STDERR_FILENO);
}

void	p_error_exist(char *av)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	ft_putstr_fd(av, STDERR_FILENO);
	ft_putstr_fd_jump(": No such file or directory", STDERR_FILENO);
}

void	ft_check_error_parser(int ac, char **av)
{
	(void)ac;
	if (ft_strcmp(av[1], "here_doc") != 0)
	{
		if (access(av[1], F_OK) == 0)
		{
			if (access(av[1], R_OK) == -1)
				p_error_perm(av[1]);
		}
		else
			p_error_exist(av[1]);
	}
}

bool	add_detail_quotes(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

char	*join_strs(t_data *data, char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup_pipe(data, add));
	tmp = str;
	str = ft_strjoin(data->mall, tmp, add);
	//free_tmp(tmp);
	return (str);
}

int		errmsg_cmd(t_data *data, char *command, char *detail, char *error_message, int error_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(command);
	msg = ft_strdup_pipe(data,"minishell: ");
	if (command != NULL)
	{
		msg = join_strs(data, msg, command);
		msg = join_strs(data, msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = join_strs(data, msg, "`");
		msg = join_strs(data, msg, detail);
		if (detail_quotes)
			msg = join_strs(data, msg, "'");
		msg = join_strs(data, msg, ": ");
	}
	msg = join_strs(data, msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	//free_tmp(msg);
	return (error_nb);
}


void errmsg_cmd(t_data *data)
{
    char *msg;
    bool detail_quotes;

    detail_quotes = add_detail_quotes(data->error_info.command);
    msg = ft_strdup_pipe(data, "minishell: ");
    if (data->error_info.command != NULL)
    {
        msg = join_strs(data, msg, data->error_info.command);
        msg = join_strs(data, msg, ": ");
    }
    if (data->error_info.detail != NULL)
    {
        if (detail_quotes)
            msg = join_strs(data, msg, "`");
        msg = join_strs(data, msg, data->error_info.detail);
        if (detail_quotes)
            msg = join_strs(data, msg, "'");
        msg = join_strs(data, msg, ": ");
    }
    msg = join_strs(data, msg, data->error_info.error_message);
    ft_putendl_fd(msg, STDERR_FILENO);
}

// Utilisation de la fonction errmsg_cmd
data->error_info.command = "my_command";
data->error_info.detail = "my_detail";
data->error_info.error_message = "my_error_message";
data->error_info.error_nb = 42;

errmsg_cmd(data);
