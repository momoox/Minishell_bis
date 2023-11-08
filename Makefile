# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: momox <momox@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 20:23:57 by momox             #+#    #+#              #
#    Updated: 2023/11/08 23:20:11 by momox            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                     CONFIG                                   #
################################################################################

NAME		:= minishell
CC			:=	gcc
CFLAGS		:=	-Wall -Wextra -Werror
HEADER		:= -I ./header
LIB			:= -lreadline -L /opt/homebrew/Cellar/readline/8.2.1/lib
INCLUDE 	:= -I /opt/homebrew/Cellar/readline/8.2.1/include/ 

ifeq ($(42),1)
	LIB = -lreadline -L /Users/$$USER/.brew/opt/readline/lib
	INCLUDE = -I /Users/$$USER/.brew/opt/readline/include
	CC = gcc
	CFLAGS = -Wall -Wextra #-Werror
endif

ifeq ($(DEBUG), 1)
	CFLAGS	+=	-g3 -fsanitize=address
endif

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################



SRCS = main.c init_struct.c print_tab.c print_token.c\
		print_list.c \
		libft/ft_strchr.c \
		libft/ft_strdup.c \
		libft/ft_strncmp.c \
		libft/ft_strjoin.c \
		libft/ft_substr.c \
		libft/tab_env.c \
		libft/env_check.c \
		libft/env_replace.c \
		libft/ft_putstr.c \
		libft/ft_putendl.c \
		libft/ft_split.c \
		libft/ft_tab_addback.c \
		libft/ft_itoa.c \
		libft/malloc_plus_plus.c \
		parser/parser.c \
		parser/check_quote.c \
		parser/check_char.c \
		parser/erase_quote.c \
		parser/is_operator.c \
		parser/split_commands.c \
		parser/whitespace.c \
		parser/ft_split_whitespaces.c \
		parser/ft_split_operators.c \
		parser/tab_exec.c \
		parser/file_inout.c \
		parser/tokenize.c \
		parser/cmd_tab.c \
		parser/check_exit_var.c \
		parser/ft_signals.c \
		parser/file_manage.c \
		lists/list_utils.c \
		lists/list_utils_2.c \
		exec/src/ft_exec_pipe.c \
		exec/src/path_cmd.c \
		exec/src/processes.c \
		exec/utils/debug.c \
		exec/utils/ft_error.c \
		exec/utils/ft_split_pipe.c \
		exec/utils/ft_strcmp.c \
		exec/utils/utils_str.c \
		builtins/ft_echo.c \
		builtins/ft_env.c \
		builtins/ft_pwd.c \

OBJECTS = $(SRCS:.c=.o)



OBJS_DIR		:=	.objs
OBJECTS =  $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))


$(OBJS_DIR)/%.o:%.c
	@mkdir -p $(dir $@)
	@ $(CC) $(INCLUDE) $(HEADER) $(CFLAGS) -c $< -o $@ 

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:=	\033[0m
RED			:=	\033[1;31m
GREEN		:=	\033[1;32m
YELLOW		:=	\033[1;33m
BLUE		:=	\033[1;34m
CYAN 		:=	\033[1;36m
RM			:=	rm -rf

all:			$(NAME)

$(NAME):		$(OBJECTS)
				@ echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
				@ $(CC) $(INCLUDE) $(HEADER) $(CFLAGS) -o $(NAME) $(LIB) $(OBJECTS)
				@ echo "$(GREEN)$(NAME) created[0m ✔️"

clean:
				@ $(RM) $(OBJS_DIR)
				@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:			clean
				@ $(RM) $(NAME)
				@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:				fclean all

.PHONY:			all clean fclean re bonus