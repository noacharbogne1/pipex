# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 08:15:54 by ncharbog          #+#    #+#              #
#    Updated: 2024/12/13 09:32:09 by ncharbog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

NAME = pipex

SRC = parsing.c \
	free_and_errors.c \
	libft_modified.c

OBJ_DIR = .objects
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBFT_DIR = libft
OBJ_LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ft_printf
OBJ_PRINTF = $(PRINTF_DIR)/libftprintf.a

all: $(NAME)

$(OBJ_LIBFT):
	cd $(LIBFT_DIR) && make
	cd $(PRINTF_DIR) && make

$(NAME): $(OBJ) $(OBJ_LIBFT) $(OBJ_PRINTF)
	$(CC) $(OBJ) $(OBJ_LIBFT) $(OBJ_PRINTF) -L$(LIBFT_DIR) -I$(LIBFT_DIR) -L$(PRINTF_DIR) -I$(PRINTF_DIR) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -O0 -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(OBJ_LIBFT) $(OBJ_PRINTF)
	cd $(LIBFT_DIR) && make clean
	cd $(PRINTF_DIR) && make clean
fclean: clean
	rm -f $(NAME)
re:	fclean all

.PHONY: all clean fclean re