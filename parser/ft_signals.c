/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:42:33 by momox             #+#    #+#             */
/*   Updated: 2023/10/21 22:27:01 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
		rl_redisplay();
}

void	sig_ignore(int signum)
{
	if (signum == SIGINT)
		rl_redisplay();
	if (signum == SIGQUIT)
		rl_redisplay();
}

void	sig_onoff(int i)
{
	rl_catch_signals = 1;
	if (i == 0)
	{
		signal(SIGINT, sig_ignore);
		signal(SIGQUIT, sig_ignore);
	}
	if (i == 1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
	}
}

void	sig_hd(int signo)
{
	if (signo == SIGINT)
		exit (0);
}
