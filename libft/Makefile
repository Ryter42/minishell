# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 21:28:46 by emoreau           #+#    #+#              #
#    Updated: 2023/03/31 23:46:50 by emoreau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#Dossier et fichier
SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
GNL_DIR = ./get_next_line/
PRINTF_DIR = ./printf/

SRCS = $(SRC_DIR)ft_strlen.c\
		$(SRC_DIR)ft_isalpha.c\
		$(SRC_DIR)ft_isalnum.c\
		$(SRC_DIR)ft_isascii.c\
		$(SRC_DIR)ft_isdigit.c\
		$(SRC_DIR)ft_isprint.c\
		$(SRC_DIR)ft_memset.c\
		$(SRC_DIR)ft_bzero.c\
		$(SRC_DIR)ft_memcpy.c\
		$(SRC_DIR)ft_memmove.c\
		$(SRC_DIR)ft_strlcpy.c\
		$(SRC_DIR)ft_strlcat.c\
		$(SRC_DIR)ft_toupper.c\
		$(SRC_DIR)ft_tolower.c\
		$(SRC_DIR)ft_strchr.c\
		$(SRC_DIR)ft_strrchr.c\
		$(SRC_DIR)ft_strncmp.c\
		$(SRC_DIR)ft_memchr.c\
		$(SRC_DIR)ft_memcmp.c\
		$(SRC_DIR)ft_strnstr.c\
		$(SRC_DIR)ft_atoi.c\
		$(SRC_DIR)ft_calloc.c\
		$(SRC_DIR)ft_strdup.c\
		$(SRC_DIR)ft_substr.c\
		$(SRC_DIR)ft_strjoin.c\
		$(SRC_DIR)ft_strtrim.c\
		$(SRC_DIR)ft_split.c\
		$(SRC_DIR)ft_itoa.c\
		$(SRC_DIR)ft_strmapi.c\
		$(SRC_DIR)ft_striteri.c\
		$(SRC_DIR)ft_putchar_fd.c\
		$(SRC_DIR)ft_putstr_fd.c\
		$(SRC_DIR)ft_putendl_fd.c\
		$(SRC_DIR)ft_putnbr_fd.c\
		$(SRC_DIR)ft_lstnew.c\
		$(SRC_DIR)ft_lstadd_front.c\
		$(SRC_DIR)ft_lstsize.c\
		$(SRC_DIR)ft_lstlast.c\
		$(SRC_DIR)ft_lstadd_back.c\
		$(SRC_DIR)ft_lstdelone.c\
		$(SRC_DIR)ft_lstclear.c\
		$(SRC_DIR)ft_lstiter.c\
		$(SRC_DIR)ft_lstmap.c\
		$(GNL_DIR)get_next_line.c\
		$(GNL_DIR)get_next_line_utils.c\
		$(PRINTF_DIR)ft_printf.c\
		$(PRINTF_DIR)printarg.c\
		$(PRINTF_DIR)putnbr.c

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))

NAME = libft.a

#Compilateur et option
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
# MACFLAG	=	-arch arm64
# LDLIBS = -I ./printf -L./printf -lftprintf

all : ${NAME}

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS} $(LDLIBS)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	${RM} $(OBJ_DIR)

fclean : clean	
	${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re