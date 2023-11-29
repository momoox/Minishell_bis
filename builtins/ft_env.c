/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:22:01 by momox             #+#    #+#             */
/*   Updated: 2023/11/29 03:50:16 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

int	get_env_var_index(t_data *data, char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(data->mall, var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*get_env_var_value(t_data *data, char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(data->mall, var, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
			return (ft_strchr(env[i], '=') + 1);
		i++;
	}
	return (NULL);
}

void	update_wds(t_data *data, char *wd)
{ 
	set_env_var(data, "OLDPWD", get_env_var_value(data, data->env, "PWD"));
	set_env_var(data, "OLDPWD", wd);
	if (data->shell->old_pwd)
		data->shell->old_pwd = ft_strdup_pipe(data, data->shell->cwd);
	if (data->shell->cwd)
		data->shell->cwd = ft_strdup_pipe(data, wd);
}

int	ft_env(t_data *data, char **env)
{
	(void)env;
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
