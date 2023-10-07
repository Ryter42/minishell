# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 19:25:41 by emoreau           #+#    #+#              #
#    Updated: 2023/10/06 18:49:22 by emoreau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	./srcs/
OBJ_DIR		=	./obj/

SRCS		=	shell/main.c

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
BONUS_OBJS = $(patsubst %.c,$(BONUS_OBJ_DIR)%.o,$(SRCS_BONUS))

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3
RM		=	rm -rf

all:	${NAME}

$(NAME):	$(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lreadline libft/libft.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) -C libft clean

fclean:	clean
		${RM} ${NAME}
		$(MAKE) -C libft fclean

re:		fclean all

.PHONY: 	all clean fclean re