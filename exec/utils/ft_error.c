/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:11:03 by oliove            #+#    #+#             */
/*   Updated: 2023/10/22 00:38:26 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

void	ft_exit(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(0);
}

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
