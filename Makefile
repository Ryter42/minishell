# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 19:25:41 by emoreau           #+#    #+#              #
#    Updated: 2023/10/20 20:28:25 by emoreau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	./srcs/
OBJ_DIR		=	./obj/

SRCS		=	shell/main.c\
					parsing/lexer.c\
					parsing/quote.c\
					parsing/pars_utils.c\
					parsing/lexer_len.c\
					parsing/copy_word.c\
					parsing/check.c\
					parsing/token.c\
					parsing/token_sep.c


OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3
RM		=	rm -rf

all:	${NAME}

$(NAME):	$(OBJS)
	$(MAKE) -C libft
	@echo Compiling $<
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline libft/libft.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@echo Compiling $<
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) -C libft clean

fclean:	clean
		${RM} ${NAME}
		$(MAKE) -C libft fclean

re:		fclean all

.PHONY: 	all clean fclean re
