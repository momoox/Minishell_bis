/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:28:55 by oliove            #+#    #+#             */
/*   Updated: 2023/11/30 01:37:51 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

// int	exec_build(t_data *data, char **cmd)
// {
// 	int	ret;
// 	printf("exec_build_for_debug\n");
//    	printf("exec_b : cmd [0] == %s\n",*cmd);

// 	ret = CMD_NOT_FOUND;
// 	if (ft_strncmp(cmd[0], "cd", 3) == 0)
// 		ret = ft_cd2(data, cmd);
// 	else if (ft_strncmp(cmd[0], "echo", 5) == 0){
//        	printf("exec_build_echo\n");
// 		ret = ft_echo(cmd);
//     }
// 	else if (ft_strncmp(cmd[0], "env", 4) == 0)
// 		ret = ft_env(data->env);
// 	else if (ft_strncmp(cmd[0], "export", 7) == 0)
// 		ret = ft_export(data,cmd);
// 	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
// 		ret = ft_pwd();
// 	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
// 		ret = ft_unset(data, cmd);
// 	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
// 		ret = ft_exit(data, cmd);
// 	printf("end EXEC_build\n");
// 	return (ret);
// }

bool	is_build(char **cmd)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (true);
	return (false);
}

t_builtin	*get_builting(void)
{
	t_builtin	builtins[8];

	builtins[0] = (t_builtin){"cd", ft_cd2};
	builtins[1] = (t_builtin){"echo", ft_echo};
	builtins[2] = (t_builtin){"env", ft_env};
	builtins[3] = (t_builtin){"export", ft_export};
	builtins[4] = (t_builtin){"pwd", ft_pwd};
	builtins[5] = (t_builtin){"unset", ft_unset};
	builtins[6] = (t_builtin){"exit", ft_exit};
	builtins[7] = (t_builtin){NULL, NULL};
	return (builtins);
}

t_builtin_func	find_builtin(const char *cmd_name, t_builtin *builtins)
{
	int	i;

	i = 0;
	while (get_builting()[i].cmd_name != NULL)
	{
		if (ft_strcmp(cmd_name, get_builting()[i].cmd_name) == 0)
		{
			return (get_builting()[i].func);
		}
		i++;
	}
	return (NULL);
}

///////////////////////////////////////////
int	exec_build(t_data *data, char **cmd)
{
	int				ret;
	t_builtin_func	func;

	ret = EXIT_SUCCESS;
	func = find_builtin(cmd[0], get_builting());
	if (func != NULL)
		return (func(data, cmd));
	else
		return (CMD_NOT_FOUND);
}

int	run_builtin(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (get_builting()[i].cmd_name != NULL)
	{
		if (ft_strcmp(cmd[0], get_builting()[i].cmd_name) == 0)
		{
			return (get_builting()[i].func(data, cmd));
		}
		i++;
	}
	return (CMD_NOT_FOUND);
}
