/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:13:11 by momox             #+#    #+#             */
/*   Updated: 2023/11/29 19:02:09 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_heredoc(pid_t pid, char *line, char *bp, int fd)
{
	if (pid == 0)
	{
		signal(SIGINT, sig_hd);
		while (1)
		{
			line = readline("> ");
			ft_putendl_fd(line, fd);
			if (!(ft_strncmp(line, bp, ft_strlen(line) + ft_strlen(bp)))
				|| line == NULL)
				break ;
			//free(line);
		}
		exit (0);
	}
}

void	ft_here_doc(char *bp, t_data *data)
{
	char	*line;
	int		fd;
	pid_t	pid;

	line = NULL;
	fd = open(".heredocminishelltrobien", O_RDWR | O_CREAT | O_TRUNC, 0644);
	sig_onoff(0);
	pid = fork();
	exec_heredoc(pid, line, bp, fd);
	waitpid(pid, 0, 0);
	sig_onoff(1);
	close(fd);
	// unlink(".heredocminishelltrobien");
	data->flag_unlink = 1;
	//free(line);
}

int heredoc_manage(t_list *temp, t_data *data)
{
	if (!temp->next)
	{
		printf("Minishell: syntax error near unexpected token `newline'\n");
		data->exit_code = 258;
		return (0);
	}
	ft_here_doc(temp->next->content, data);
	temp->token = REDIR_I;
	temp->content = ".heredocminishelltrobien";
	ft_lstdel_here(&data->list, temp->next);
	return (1);
}

int	tokenize(t_data *data)
{
	t_list	*temp;

	temp = data->list;
	while (temp)
	{
		if (!(ft_strncmp(temp->content, "|", 1)))
			temp->token = PIPE;
		else if (!(ft_strncmp(temp->content, "<<", 2)))
		{
			if (!heredoc_manage(temp, data))
				return (0);
		}
		else if (!(ft_strncmp(temp->content, ">>", 2)))
			temp->token = REDIR_A;
		else if (!(ft_strncmp(temp->content, "<", 1)))
			temp->token = REDIR_I;
		else if (!(ft_strncmp(temp->content, ">", 1)))
			temp->token = REDIR_O;
		else if (temp->prev
			&& (temp->prev->token == REDIR_I || temp->prev->token == REDIR_O
				|| temp->prev->token == REDIR_A))
			temp->token = FILES;
		else
			temp->token = COMMAND;
		temp = temp->next;
	}
	return (1);
}
	 	