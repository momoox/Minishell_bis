/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:24:08 by oliove            #+#    #+#             */
/*   Updated: 2023/11/03 18:48:36 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;
	int				readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		if (stash != NULL)
			stash = free_stash(stash);
		return (NULL);
	}
	readed = 1;
	line = NULL;
	read_and_stash(fd, &stash, &readed);
	if (stash == NULL)
		return (NULL);
	extract_line(stash, &line);
	update_stash(&stash);
	if (line[0] != '\0')
		return (line);
	free_stash(stash);
	stash = NULL;
	free(line);
	return (NULL);
}

void	read_and_stash(int fd, t_list **stash, int *readed_ptr)
{
	char	*buff;

	while (!found_newline(*stash) && *readed_ptr != 0)
	{
		buff = malloc_plus_plus(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		*readed_ptr = (int)read(fd, buff, BUFFER_SIZE);
		if ((*stash == NULL && *readed_ptr == 0) || *readed_ptr == -1)
		{
			if (stash != NULL)
			{
				free_stash(*stash);
			}
			free(buff);
			return ;
		}
		buff[*readed_ptr] = '\0';
		add_to_stash(stash, buff, *readed_ptr);
		free(buff);
	}
}

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

char	*extract_substring_after_newline(char *str)
{
	int		i;
	int		len;
	char	*sub;
	int		j;

	i = 0;
	len = 0;
	while (str[len] != '\0')
		len++;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	sub = malloc_plus_plus(sizeof(char) * (len - i + 1));
	if (sub == NULL)
		return (NULL);
	j = 0;
	while (str[i])
		sub[j++] = str[i++];
	sub[j] = '\0';
	return (sub);
}

void	update_stash(t_list **stash)
{
	t_list	*last;
	char	*clean_str;
	t_list	*new_node;

	if (*stash == NULL)
		return ;
	last = ft_lst_get_last(*stash);
	clean_str = extract_substring_after_newline(last->content);
	if (clean_str == NULL)
		return ;
	new_node = malloc_plus_plus(sizeof(t_list));
	if (new_node == NULL)
	{
		free(clean_str);
		return ;
	}
	new_node->content = clean_str;
	new_node->next = NULL;
	free_stash(*stash);
	*stash = new_node;
}
