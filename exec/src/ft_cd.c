/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:53:37 by oliove            #+#    #+#             */
/*   Updated: 2023/11/28 22:29:32 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"


int	chdir_errno_mod(char *path, t_data *data)
{
	if (errno == ESTALE)
		errno = ENOENT;
	errmsg_cmd(data,"cd", path, strerror(errno), errno);
	return (0);
}

int	change_dir(t_data *data, char *path)
{
	printf("in change dir\n");
	char	*ret;
	char	*tmp;
	char	cwd[PATH_MAX];

	ret = NULL;
	if (chdir(path) != 0)
		return (chdir_errno_mod(path, data));
	ret = getcwd(cwd, PATH_MAX);
	if (!ret)
	{
		errmsg_cmd(data, "cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		ret = ft_strjoin(data->mall, data->shell->cwd, "/");
		tmp = ret;
		ret = ft_strjoin(data->mall, tmp, path);
	}
	else
		ret = ft_strdup_pipe(data, cwd);
	// printf("ch_dir ret = %s \n ", ret);
	update_wds(data, ret);
	return (EXIT_SUCCESS);
}

int	ft_cd2(t_data *data, char **args)
{
	printf("in cd2\n");
	char	*path;

	if (!args || !args[1] || ft_isspace(args[1][0]) || args[1][0] == '\0'
		|| ft_strncmp(args[1], "--", 3) == 0 || ft_strncmp(args[1], "~", 2) == 0)
	{
		path = get_env_var_value(data, data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd(data,"cd", NULL, "HOME not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	if (args[2])
		return (errmsg_cmd(data, "cd", NULL, "too many arguments", EXIT_FAILURE));
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_var_value(data, data->env,
				"OLDPWD");
		if (!path)
			return (errmsg_cmd(data, "cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		return (!change_dir(data, path));
	}
	return (!change_dir(data, args[1]));
}

