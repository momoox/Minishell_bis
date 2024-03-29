/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:44:52 by oliove            #+#    #+#             */
/*   Updated: 2023/11/30 10:11:03 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "util_exec.h"

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if ((neg == 1 && num > LONG_MAX) || (
			neg == -1 && num > -(unsigned long)LONG_MIN))
		*error = true;
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return (num * neg);
}

static int	get_exit_code(t_data *data, char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (data->exit_code);
	i = 0;
	while (ft_isspace(arg[i]))
		i++;
	if (arg[i] == '\0')
		*error = true;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && !ft_isspace(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return (i % 256);
}

void	exit_shell(t_data *data, int ret)
{
	if (data)
		free_mall(&data->mall);
	exit(ret);
}

int	ft_exit(t_data *data, char **args)
{
	bool	error;
	int		exit_code;

	error = false;
	if (!args || !args[1])
		exit_code = data->exit_code;
	else
	{
		exit_code = get_exit_code(data, args[1], &error);
		if (error)
		{
			errmsg_cmd(data, (char *[3]){"exit", args[1],
				"numeric argument required"}, 2);
			exit_code = 255;
		}
		else if (args[2])
			return (errmsg_cmd(data, (char *[3]){"exit", NULL,
					"too many arguments"}, 1));
	}
	exit_shell(data, exit_code);
	return (2);
}
