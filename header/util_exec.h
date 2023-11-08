/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:16:06 by oliove            #+#    #+#             */
/*   Updated: 2023/11/03 22:48:10 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_EXEC_H
# define UTIL_EXEC_H

// # include "../lib/get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "minishell.h"

void	ft_putstr_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd_jump(char *str, int fd);
int		ft_strlen_pipe(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	**ft_split_pipe(t_mall *mall, char const *s, char c);
char	*ft_strjoin_pipe(t_mall *mall, char const *s1, char const *s2);

void	*ft_path_dir(char *cmd, char *path, int i);
// void	exece(t_data *data,char **cmd, char **env);
void	exece(t_data *data, char **cmd, char **env);
int		file_o(char *file, int token);
void	ft_pipe(t_data *data);//, char *cmd, char **env);
// void	ft_here_doc(char **av);
void	ft_here_doc_put_in(char **av, int *p_fd);

void	ft_exit(int n_exit);
void	p_error_perm(char *av);
void	p_error_exist(char *av);
void	ft_check_error_parser(int ac, char **av);
void	run_exec(t_data *data);
char	*ft_my_var(t_data *data, char *str);
char	*ft_my_path(t_data *data, char *cmd, char **env);
char	*ft_strjoin_pipe(t_mall *mall, char const *s1, char const *s2);
char	*ft_strjoin_pipe2(t_mall *mall, char const *s1, char const *s2);

//Debug
void	print_debug(t_data *data);
// Exec


#endif