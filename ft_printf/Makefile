# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 14:57:09 by ncharbog          #+#    #+#              #
#    Updated: 2024/10/22 09:48:13 by ncharbog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS += -Wall -Werror -Wextra

NAME = libftprintf.a

SRC = ft_printf.c\
	utils_p_and_u.c\
	utils.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re:	fclean all

.PHONY: all clean fclean re bonus