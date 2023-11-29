/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:22:10 by momox             #+#    #+#             */
/*   Updated: 2023/11/29 15:59:43 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

int	ft_pwd(t_data *data, char **args)
{
	char	buf[PATH_MAX];
	char	*cwd;

	(void)args;
	if (data->shell->cwd)
	{
		ft_putendl_fd(data->shell->cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(buf, PATH_MAX);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	// errmsg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}
