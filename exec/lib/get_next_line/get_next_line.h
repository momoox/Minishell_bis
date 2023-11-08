/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 20:28:28 by oliove            #+#    #+#             */
/*   Updated: 2023/03/14 16:31:32 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_tlist
{
	char			*content;
	struct s_tlist	*next;
}					t_list;

char				*get_next_line(int fd);
void				read_and_stash(int fd, t_list **stash, int *readed_ptr);
t_list				*free_stash(t_list *stash);
int					ft_strlen(const char *str);
void				add_to_stash(t_list **stash, char *buff, int readed);
void				extract_line(t_list *stash, char **line);
void				generate_line(char **line, t_list *stash);
void				clean_stash(t_list **stash);
int					found_newline(t_list *stash);
t_list				*ft_lst_get_last(t_list *stash);
void				update_stash(t_list **stash);
char				*extract_substring_after_newline(char *str);
void				free_stash_and_return_null(t_list *stash);

#endif