/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 03:46:07 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 17:33:45 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

int	set_env_var(t_data *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(data, data->env, key);
	if (value == NULL)
		tmp = "";
	else
		tmp = ft_strjoin(data->mall, "=", value);
	if (!tmp)
		return (1);
	if (idx != -1 && data->env[idx])
		data->env[idx] = ft_strjoin(data->mall, key, tmp);
	else
	{
		idx = env_var_count(data->env);
		data->env = realloc_env(data, idx + 1);
		if (!data->env)
			return (1);
		data->env[idx] = ft_strjoin(data->mall, key, tmp);
	}
	return (0);
}

int	remove_env_var(t_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(data->env))
		return (1);
	i = idx;
	count = idx;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup_pipe(data, data->env[i + 1]);
		count++;
		i++;
	}
	data->env = realloc_env(data, count);
	if (!data->env)
		return (false);
	return (0);
}

int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

bool	is_valid_env_var_key(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (false);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	env_build(t_data *data, char **args)
{
	int i;

	if (args && args[1])
		(errmsg_cmd(data, (char *[3]){"env", NULL, "too many arguments"}, 2));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}