/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 00:53:27 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 05:18:47 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_exec.h"

// void	free_tmp(char *str)
// {
// 	if (str != NULL)
// 	{
// 		//free(str);
// 		str = NULL;
// 	}
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char	**get_key_value_pair(t_data *data, char *arg)
{
	char	**tmp;
	char	*eq_pos;

	eq_pos = ft_strchr(arg, '=');
	tmp = malloc_plus_plus(&data->mall, sizeof *tmp * (2 + 1));
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
	i = 1;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
		{
			errmsg_cmd(data, "export", args[i], "not a valid identifier", false);
			ret = EXIT_FAILURE;
			return (ret);
		}
		else if (ft_strchr(args[i], '=') != NULL)
		{
			tmp = get_key_value_pair(data, args[i]);
			set_env_var(data, tmp[0], tmp[1]);
			// free_tab_args(tmp);
		}
		else
		{
			set_env_var(data, args[i], NULL);
		}
		i++;
	}
	return (ret);
}


int compare_env_vars(const void *a, const void *b)
{
    const char *env_var_a = *(const char **)a;
    const char *env_var_b = *(const char **)b;
    return strcmp(env_var_a, env_var_b);
}

int ft_export(t_data *data, char **args)
{
    int i;
    int ret;

    ret = EXIT_SUCCESS;
    i = 0;

    if (!args[1])
    {
        int env_count = 0;
        while (data->env[env_count])
            env_count++;
        char **env_copy = (char **)malloc_plus_plus(data, (env_count + 1) * sizeof(char *));
        if (!env_copy)
            return EXIT_FAILURE;
        for (int i = 0; i < env_count; i++)
            env_copy[i] = ft_strdup(datam data->env[i]);
        env_copy[env_count] = NULL;
        qsort(env_copy, env_count, sizeof(char *), compare_env_vars);
        for (int i = 0; i < env_count; i++)
            ft_putendl_fd(env_copy[i], STDOUT_FILENO);
    }
    return ret;
}
