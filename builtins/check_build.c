/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_build.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:28:55 by oliove            #+#    #+#             */
/*   Updated: 2023/11/29 22:15:45 by oliove           ###   ########.fr       */
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
void get_builting()
{
    
}
t_builtin		builtins[] = {{"cd", ft_cd2},
						{"echo", ft_echo},
						{"env", ft_env},
						{"export", ft_export},
						{"pwd", ft_pwd},
						{"unset", ft_unset},
						{"exit", ft_exit},

						{NULL, NULL}};

builtin_func	find_builtin(const char *cmd_name, t_builtin *builtins)
{
	int	i;

	i = 0;
	while (builtins[i].cmd_name != NULL)
	{
		if (ft_strcmp(cmd_name, builtins[i].cmd_name) == 0)
		{
			return (builtins[i].func);
		}
		i++;
	}
	return (NULL); // Commande non trouvée
}

///////////////////////////////////////////
int	exec_build(t_data *data, char **cmd)
{
	int				ret;
	builtin_func	func;

	ret = EXIT_SUCCESS;
	func = find_builtin(cmd[0], builtins);
	if (func != NULL)
		return (func(data, cmd));
	else
		return (CMD_NOT_FOUND);
}

int	run_builtin(t_data *data, char **cmd)
{
	int	i;

	i = 0;
	while (builtins[i].cmd_name != NULL)
	{
		if (ft_strcmp(cmd[0], builtins[i].cmd_name) == 0)
		{
			return (builtins[i].func(data, cmd));
		}
		i++;
	}
	return (CMD_NOT_FOUND);
}
