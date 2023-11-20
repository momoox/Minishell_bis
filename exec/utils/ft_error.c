/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:11:03 by oliove            #+#    #+#             */
/*   Updated: 2023/11/20 16:07:12 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

// void	ft_exit(int n_exit)
// {
// 	if (n_exit == 1)
// 		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
// 	exit(0);
// }

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

char	*join_strs(t_mall *mall, char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup_pipe(mall, add));
	tmp = str;
	str = ft_strjoin(mall, tmp, add);
	//free_tmp(tmp);
	return (str);
}

int	errmsg_cmd(t_mall *mall, char *command, char *detail, char *error_message, int error_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(command);
	msg = ft_strdup_pipe(mall,"minishell: ");
	if (command != NULL)
	{
		msg = join_strs(mall, msg, command);
		msg = join_strs(mall, msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = join_strs(mall, msg, "`");
		msg = join_strs(mall, msg, detail);
		if (detail_quotes)
			msg = join_strs(mall, msg, "'");
		msg = join_strs(mall, msg, ": ");
	}
	msg = join_strs(mall, msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	//free_tmp(msg);
	return (error_nb);
}