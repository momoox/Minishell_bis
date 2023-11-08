/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:49:25 by momox             #+#    #+#             */
/*   Updated: 2023/11/04 20:54:14 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*identify_replace(t_mall *mall, t_data *data, char *var_env)
{
	int		i;
	char	*full_var;
	char	*replace;

	i = 0;
	full_var = ft_strjoin(mall, var_env, "=");
	while (data->env[i++])
	{
		if (ft_strncmp(full_var, data->env[i], ft_strlen(full_var)) == 0)
		{
			replace = ft_substr(mall, data->env[i], ft_strlen(full_var),
					ft_strlen(data->env[i]) - ft_strlen(full_var));
			break ;
		}
		else
			replace = NULL;
	}
	free(full_var);
	return (replace);
}

char	*replace_env(t_mall *mall, char *arg, char *replace)
{
	char	*begin;
	char	*end;
	char	*new_var;
	int		len;
	int		var;

	var = is_env(arg);
	len = env_pos(arg);
	begin = ft_substr(mall, arg, 0, len);
	new_var = ft_strjoin(mall, begin, replace);
	end = ft_substr(mall, arg, var + len + 1, ft_strlen(arg));
	new_var = ft_strjoin(mall, new_var, end);
	return (new_var);
}

char	*get_env(t_mall *mall, char *arg, int len)
{
	char	*var;
	int		start;

	start = -1;
	while (arg[++start])
		if (arg[start] == '$')
			break ;
	if (arg[start] == '$')
		start++;
	var = ft_substr(mall, arg, start, len);
	return (var);
}
