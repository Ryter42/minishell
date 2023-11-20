# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elias <elias@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 19:25:41 by emoreau           #+#    #+#              #
#    Updated: 2023/11/20 19:09:16 by elias            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	./srcs/
OBJ_DIR		=	./obj/

SRCS		=	shell/main.c\
					shell/signal.c\
					shell/get_status.c\
					parsing/lexer.c\
					parsing/quote.c\
					parsing/pars_utils.c\
					parsing/lexer_len.c\
					parsing/copy_word.c\
					parsing/check.c\
					parsing/check_sep.c\
					parsing/first_check.c\
					parsing/token.c\
					parsing/token_sep.c\
					parsing/clean.c\
					parsing/clean2.c\
					parsing/expand.c\
					parsing/expand2.c\
					parsing/rm_quote.c\
					exec/free.c\
					exec/heredoc.c\
					exec/pipex.c\
					exec/exec.c\
					exec/path.c\
					bultin/bultin.c\
					bultin/echo.c\
					bultin/pwd.c\
					bultin/cd.c\
					bultin/env.c\
					bultin/exit.c\
					bultin/export.c\
					bultin/unset.c

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3
# LDLIBS	= -lreadline
RM		=	rm -rf

all:	${NAME}

$(NAME):	$(OBJS)
	$(MAKE) -C libft
	@echo Compiling $<
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline libft/libft.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@ #-lreadline

clean:
	${RM} $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) -C libft clean

fclean:	clean
		${RM} ${NAME}
		$(MAKE) -C libft fclean

re:		fclean all

.PHONY: 	all clean fclean re
