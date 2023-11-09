/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:53:37 by oliove            #+#    #+#             */
/*   Updated: 2023/11/09 20:49:57 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"


int	chdir_errno_mod(char *path, t_mall *mall)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd(mall,"cd", path, strerror(errno), errno);
	return (0);
}

int	change_dir(t_data *data, t_mall *mall, char *path)
{
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path, mall));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		errmsg_cmd(mall, "cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		ret = ft_strjoin(mall, data->exec->shell->cwd, "/");
		tmp = ret;
		ret = ft_strjoin(mall, tmp, path);
		// //free_tmp(tmp);
	}
	else
		ret = ft_strdup_pipe(mall, cwd);
	printf("ch_dir ret = %s \n ", ret);
	update_wds(data, mall, ret);
	//free(ret);
	return (1);
}

int	ft_cd2(t_data *data, t_mall *mall, char **args)
{
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]) || args[1][0] == '\0'
		|| ft_strncmp(args[1], "--", 3) == 0)
	{
		path = /*ft_my_var(data,"HOME");*/ get_env_var_value(mall, data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd(mall,"cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, mall, path));
	}
	if (args[2])
		return (errmsg_cmd(mall, "cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = /*ft_my_var(data, "OLDPWD");*/ get_env_var_value(mall, data->env,
				"OLDPWD");
		if (!path)
			return (errmsg_cmd(mall, "cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, mall, path));
	}
	return (!change_dir(data, mall, args[1]));
	// return (0);
}

