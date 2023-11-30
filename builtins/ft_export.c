/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:53:27 by oliove            #+#    #+#             */
/*   Updated: 2023/11/30 01:29:42 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

char	**get_key_value_pair(t_data *data, char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc_plus_plus(&data->mall, sizeof (*tmp) * (2 + 1));
	tmp[0] = ft_substr_pipe(data, arg, 0, eq_pos - arg);
	tmp[1] = ft_substr_pipe(data, eq_pos, 1, ft_strlen(eq_pos));
	tmp[2] = NULL;
	return (tmp);
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	ret = EXIT_SUCCESS;
	i = 0;
	if (!args[1])
		return (ft_export2(data, args));
	while (args[++i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd(data, (char *[3]){"export", args[i],
				"not a valid identifier"}, false);
			return (EXIT_FAILURE);
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(data, args[i]);
			set_env_var(data, tmp[0], tmp[1]);
		}
		else
			set_env_var(data, args[i], NULL);
	}
	return (ret);
}

int	compare_env_vars(const void *a, const void *b)
{
	const char	*env_var_a = *(const char **)a;
	const char	*env_var_b = *(const char **)b;

	return (strcmp(env_var_a, env_var_b));
}

int	ft_export2(t_data *data, char **args)
{
	int		i;
	int		ret;
	int		env_count;
	char	**env_copy;

	ret = EXIT_SUCCESS;
	i = 0;
	if (!args[1])
	{
		env_count = 0;
		while (data->env[env_count])
			env_count++;
		env_copy = (char **)malloc_plus_plus(&data->mall, (env_count + 1)
				* sizeof(char *));
		if (!env_copy)
			return (EXIT_FAILURE);
		while (i++ < env_count)
			env_copy[i] = ft_strdup(data, data->env[i]);
		env_copy[env_count] = NULL;
		sort_tab(env_copy);
		i = 0;
		while (i++ < env_count)
			ft_putendl_fd(env_copy[i], STDOUT_FILENO);
	}
	return (ret);
}
