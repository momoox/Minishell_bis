/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_exec.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:16:06 by oliove            #+#    #+#             */
/*   Updated: 2023/11/30 20:53:42 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_EXEC_H
# define UTIL_EXEC_H

# include "limits.h"
# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

void	ft_putstr_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd_jump(char *str, int fd);
int		ft_strlen_pipe(const char *str);
int		ft_strcmp(const char *s1, const char *s2);

char	**ft_split_pipe(t_data *mall, char const *s, char c);
char	*ft_strjoin_pipe(t_mall *mall, char const *s1, char const *s2);

void	*ft_path_dir(t_mall *mall, char *cmd, char *path, int i);
void	exece(t_data *data, char **cmd, char **env);
int		file_o(char *file, int token);
void	ft_pipe(t_data *data);

void	p_error_perm(char *av);
void	p_error_exist(char *av);
void	ft_check_error_parser(int ac, char **av);
void	run_exec(t_data *data);
char	*ft_my_var(t_data *data, char *str);
char	*ft_my_path(t_data *data, char *cmd, char **env);
char	*ft_strjoin_pipe(t_mall *mall, char const *s1, char const *s2);
char	*ft_strjoin_pipe2(t_mall *mall, char const *s1, char const *s2);

int		search_idx(char **env, char *key_str);
void	print_env_sort(char **env, t_mall *mall);
void	init_data_shell(t_data *data);

char	*ft_strjoin_norml(char const *s1, char const *s2);
void	*ft_calloc_env(t_data *data, size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup_pipe(t_data *data, char *src);
int		env_var_count(char **env);
char	**get_key_value_pair(t_data *data, char *arg);
int		ft_export(t_data *data, char **args);
int		ft_unset(t_data *data, char **args);
bool	is_valid_env_var_key(char *var);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		env_builtin(t_data *data, char **args);
char	*ft_substr_pipe(t_data *data, char *s, int start, int len);
void	free_tab_args(char **args);
char	*join_strs(t_data *data, char *str, char *add);

int		errmsg_cmd(t_data *data, char *msg_err[3], int error_nb);
int		ft_export2(t_data *data, char **args);

bool	add_detail_quotes(char *command);
int		ft_isspace(int c);
int		set_env_var(t_data *data, char *key, char *value);
int		exec_build(t_data *data, char **cmd);

int		ft_cd2(t_data *data, char **args);
void	update_wds(t_data *data, char *wd);
int		init_env(t_data *data, char **env);
int		init_wds(t_data *data);
int		get_env_var_index(t_data *data, char **env, char *var);
int		chdir_errno_mod(char *path, t_data *data);
int		change_dir(t_data *data, char *path);
char	*get_env_var_value(t_data *data, char **env, char *var);

void	cleanup_pipes(t_data *data);
int		pipe_execution(t_data *data, int *j);
int		initialize_pipes(t_data *data, int fd_pipe[2], int *j);
int		ft_pipe2(t_exec *ex, int *fd_stdin, int *fd_stdout);
void	exit_shell(t_data *data, int ret);
int		ft_exit(t_data *data, char **args);
bool	is_build(char **cmd);
int		check_cmd_not_found(t_data *data, t_exec *cmd);

int		execute_local_bin(t_data *data, t_exec *cmd);
int		execute_command(t_data *data, t_exec *cmd);
int		execute_sys_bin(t_data *data, t_exec *cmd);
int		prep_exec(t_data *data, int *fd_pipe, int *j);
int		init_io(t_data *data, int fd_pipe[2], int *j);

int		check_path_slash(char *path, char *cmd);
int		is_forck(t_data *data, t_exec *cmd);
char	*ft_strcpy(char *dest, char *src);

char	*ft_strcat(char *dest, char *src);

char	**realloc_env(t_data *data, size_t size);
int		remove_env_var(t_data *data, int idx);
void	sort_tab(char **tab);
int		norm_cmd(int *i, int fd[], int *fd_stdin);
void	initialize_pipes2(t_data *data, int *j);
void	ft_putendl_fd2(t_data *mall, char *s, int fd);

#endif
