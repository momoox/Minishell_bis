/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:22:01 by momox             #+#    #+#             */
/*   Updated: 2023/11/24 01:08:59 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

char	*get_env_var_value(t_data *data, char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(data->mall, var, "=");
	printf("get_env_value: tmp == [%s]\n",tmp);
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			//////////free_tmp(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	//free_tmp(tmp);
	return (NULL);
}

void	update_wds(t_data *data, char *wd)
{ 
	// char *old = get_env_var_value(data->env,"PWD");
	// printf("p_old = [%s]\n",old);
	// printf("get_env UP_DATE= [%s]\n",old);
	set_env_var(data, "OLDPWD", get_env_var_value(data, data->env, "PWD"));
	printf("old_pwd = [%s]\n",wd);//data->exec->shell->hold_pwd);
	set_env_var(data, "OLDPWD", wd);
	if (data->shell->hold_pwd)
	{
		//free_tmp(data->exec->shell->hold_pwd);
		data->shell->hold_pwd = ft_strdup_pipe(data, data->shell->cwd);
		printf("get_env dat= [%s]\n",data->shell->pwd);
	}
	if (data->shell->cwd)
	{
		//free_tmp(data->shell->cwd);
		data->shell->cwd = ft_strdup_pipe(data, wd);
	}
	//free_tmp(wd);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
