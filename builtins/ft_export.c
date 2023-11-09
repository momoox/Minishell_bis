/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:53:27 by oliove            #+#    #+#             */
/*   Updated: 2023/11/09 20:49:57 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

void	free_tmp(char *str)
{
	if (str != NULL)
	{
		//free(str);
		str = NULL;
	}
}

int	get_env_var_index(t_mall *mall, char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(mall, var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			//free_tmp(tmp);
			return (i);
		}
		i++;
	}
	//free_tmp(tmp);
	return (-1);
}


char	**realloc_env(t_data *data, t_mall *mall, size_t size)
{
	char	**new_env;
	size_t	i;

	new_env = ft_calloc_env(mall, size + 1, sizeof *new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(mall, data->env[i]);
		//free_tmp(data->env[i]);
		i++;
	}
	// //free(data->env);
	return (new_env);
}

int	set_env_var(t_data *data, t_mall *mall, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(mall, data->env, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin(mall, "=", value);
	if (!tmp)
		return (1);
	if (idx != -1 && data->env[idx])
	{
		//free_tmp(data->env[idx]);
		data->env[idx] = ft_strjoin(mall, key, tmp);
	}
	else
	{
		idx = env_var_count(data->env);
		data->env = realloc_env(data, mall, idx + 1);
		if (!data->env)
			return (1);
		data->env[idx] = ft_strjoin(mall, key, tmp);
	}
	//free_tmp(tmp);
	return (0);
}

int	remove_env_var(t_data *data,t_mall *mall, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(data->env))
		return (1);
	//free_tmp(data->env[idx]);
	i = idx;
	count = idx;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup_pipe(mall, data->env[i + 1]);
		//free_tmp(data->env[i + 1]);
		count++;
		i++;
	}
	data->env = realloc_env(data, mall, count);
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

void	*ft_calloc_env(t_mall *mall, size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc_plus_plus(&mall, count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

char	**get_key_value_pair(t_mall *mall, char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc_plus_plus(&mall, sizeof *tmp * (2 + 1));
	tmp[0] = ft_substr_pipe(mall, arg, 0, eq_pos - arg);
	tmp[1] = ft_substr_pipe(mall, eq_pos, 1, ft_strlen(eq_pos));
	tmp[2] = NULL;
	return (tmp);
}

int	ft_export(t_data *data, t_mall *mall, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 1;
	if (!args[i])
		return (env_builtin(data,mall, NULL));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd(mall, "export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(mall, args[i]);
			set_env_var(data, mall, tmp[0], tmp[1]);
			// free_tab_args(tmp);
		}
		i++;
	}
	return (ret);
}

int	ft_unset(t_data *data, t_mall *mall, char **args)
{
	int	i;
	int	idx;
	int	ret;

	ret = EXIT_SUCCESS;
	i = 1;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]) || ft_strchr(args[i], '=') != NULL)
		{
			errmsg_cmd(mall,"unset", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else
		{
			idx = get_env_var_index(mall, data->env, args[i]);
			if (idx != -1)
				remove_env_var(data, mall, idx);
		}
		i++;
	}
	return (ret);
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

int	env_builtin(t_data *data,t_mall *mall, char **args)
{
	int i;

	if (args && args[1])
		(errmsg_cmd(mall,"env", NULL, "too many arguments", 2));
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}