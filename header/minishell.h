/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momox <momox@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:38:23 by mgeisler          #+#    #+#             */
/*   Updated: 2023/11/30 20:19:35 by momox            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

enum				e_token
{
	PIPE = 0,
	FILES = 1,
	COMMAND = 2,
	REDIR_I = 3,
	REDIR_A = 4,
	REDIR_O = 5,
	REDIR_HERE_DOC = 6,
};

typedef struct s_mall
{
	void			*content;
	struct s_data	*data;
	struct s_mall	*next;
	struct s_mall	*prev;
}					t_mall;

typedef struct s_list
{
	char			*content;
	char			**cmd;
	enum e_token	token;
	struct s_list	*next;
	struct s_list	*prev;
	struct s_data	*data;
}					t_list;

typedef struct s_error_info
{
	char			*command;
	char			*detail;
	char			*error_message;
	int				error_nb;
}					t_error_info;

typedef struct s_exec_shell
{
	char			*cwd;
	char			*old_pwd;
}					t_exec_shell;

typedef struct s_exec
{
	t_list			*stdin_st;
	int				fd_in;
	int				fd_out;
	int				fd_pipe[2];
	int				pid;
	t_list			*stdout_st;
	char			**cmd;
	char			*path;
	t_exec_shell	*shell;
}					t_exec;

struct				s_data;

typedef int			(*t_builtin_func)(struct s_data *data, char **cmd);

typedef struct s_builtin
{
	const char		*cmd_name;
	t_builtin_func	func;
}					t_builtin;

typedef struct s_data
{
	int				flag_unlink;
	int				flag_delete;
	char			*input;
	int				nb_exec;
	char			**env;
	char			**parsed_line;
	int				exit_code;
	t_mall			*mall;
	t_exec			*exec;
	t_list			*list;
	t_exec_shell	*shell;
	pid_t			pid;
	t_builtin		*func;
	t_error_info	error_info;
}					t_data;

t_builtin_func		find_builtin(t_data *data, const char *cmd_name);
int					exec_build(t_data *data, char **cmd);

char				*ft_strchr(const char *str, int search);
char				*ft_strdup(t_data *data, char *src);
size_t				ft_strlcpy(char *dest, char *src, size_t size);
int					ft_strlen(char *str);
int					ft_strncmp(char *s1, char *s2, size_t len);
void				tab_env(t_data *data, char **env);
char				*ft_substr(t_mall *mall, char *s, int start, int len);
void				env_check(t_data *data);
int					is_env(char *arg);
int					env_pos(char *arg);
char				*get_env(t_mall *mall, char *arg, int len);
char				*replace_env(t_mall *mall, char *arg, char *replace);
char				*identify_replace(t_mall *mall, t_data *data,
						char *var_env);
char				*ft_strjoin(t_mall *mall, char *s1, char *s2);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
char				**ft_split(t_mall *mall, char *s, char c);
char				**ft_tabadd_back(t_mall *mall, char **tab, char *new_str);
char				*ft_itoa(t_mall *mall, int n);
void				*malloc_plus_plus(t_mall **mall, size_t size);
void				free_mall(t_mall **mall);
int					ft_strchr_char(const char *str, char *s);
char				**ft_tabdup(t_data *data, char **tab);

void				reader(t_data *data);

void				sig_handler(int signo);
void				sig_ignore(int signum);
void				sig_onoff(int i);
void				sig_hd(int signo);
int					parser(t_data *data);
int					check_char(char *str, t_data *data);
char				check_quote(char *str, t_data *data);
char				*quote_remove(t_mall *mall, char *str);
void				quote_index(char *str, int *index_tab);
void				check_quote_remove(t_data *data, t_list *list);
char				*erase_quote(t_mall *mall, char *str, int *index_tab);
char				is_between_quote(char *str, int index);
char				is_between_quote_rem(char *str, int index);
int					is_operator(char c);
void				ft_here_doc(char *bp, t_data *data);
int					split_op(t_data *data, char c);
void				split_line(t_data *data);
void				split_hd(t_data *data, t_list *list);
int					tokenize(t_data *data);
int					check_token(t_data *data);
void				exec_heredoc(pid_t pid, char *line, char *bp, int fd);
void				tab_exec(t_data *data);
void				file_manage(t_data *data, t_list *temp, int i);
void				cmd_tab(t_data *data);
void				check_exit_var(t_data *data);
void				redir_in_manage(t_data *data, t_list *list, int i);
void				redir_out_manage(t_data *data, t_list *list, int i);
void				redir_append_manage(t_data *data, t_list *list, int i);
void				redir_error(t_data *data, t_list *list);

char				**ft_split_operators(t_mall *mall, char *s, char c);
char				**ft_split_whitespaces(t_mall *mall, char *s);

int					len_input(char *s);
void				print_tab(t_data *data);

int					ft_whitespace(char c);
int					check_whitespaces(char *s);

void				lstadd_front(t_list **first, t_list *new);
void				lstadd_back(t_list **first, t_list *new);
void				lstadd_back_mall(t_mall **first, t_mall *new);
t_list				*ft_lstnew(t_mall *mall, char *str);
void				list_back(t_list *list);

void				ft_lstdel_here(t_list **first, t_list *delete);
void				ft_lstadd_here(t_list **lst, t_list *new);
int					size_list_string(t_list *list);

void				init_data(t_data *data);
void				reinit(t_data *data);

void				print_list(t_list *list);
void				print_exec(t_data *data);
void				print_tab(t_data *data);
void				printtab2(int *tab);
void				print_token(t_list *list);

int					ft_env(t_data *data, char **env);
int					ft_echo(t_data *data, char **cmd);
int					ft_pwd(t_data *data, char **null);
t_builtin			*get_builting(t_data *data);

void				run_exec(t_data *data);

#endif