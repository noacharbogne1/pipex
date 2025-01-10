# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ncharbog <ncharbog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 08:15:54 by ncharbog          #+#    #+#              #
#    Updated: 2025/01/10 11:21:57 by ncharbog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

NAME = pipex

SRC = src/exec.c \
	src/free.c \
	src/main.c \
	src/parsing.c \
	src/parsing_utils.c \
	src/libft_modified.c

BONUS_SRC = src_bonus/exec_bonus.c \
	src_bonus/free_bonus.c \
	src_bonus/main_bonus.c \
	src_bonus/parsing_bonus.c \
	src_bonus/parsing_utils_bonus.c \
	src_bonus/libft_modified_bonus.c

OBJ_DIR = .objects
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))

LIBFT_DIR = libft
OBJ_LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = ft_printf_fd
OBJ_PRINTF = $(PRINTF_DIR)/libftprintf_fd.a

all: $(NAME)

$(OBJ_LIBFT):
	cd $(LIBFT_DIR) && make

$(OBJ_PRINTF):
	cd $(PRINTF_DIR) && make

$(NAME): $(OBJ) $(OBJ_LIBFT) $(OBJ_PRINTF)
	$(CC) $(OBJ) $(OBJ_LIBFT) $(OBJ_PRINTF) -L$(LIBFT_DIR) -I$(LIBFT_DIR) -L$(PRINTF_DIR) -I$(PRINTF_DIR) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(PRINTF_DIR) -O0 -c $< -o $@

bonus: $(BONUS_OBJ) $(OBJ_LIBFT) $(OBJ_PRINTF)
	$(CC) $(BONUS_OBJ) $(OBJ_LIBFT) $(OBJ_PRINTF) -L$(LIBFT_DIR) -I$(LIBFT_DIR) -L$(PRINTF_DIR) -I$(PRINTF_DIR) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR) $(OBJ_LIBFT) $(OBJ_PRINTF)
	cd $(LIBFT_DIR) && make clean
	cd $(PRINTF_DIR) && make clean
fclean: clean
	rm -f $(NAME)
re:	fclean all

.PHONY: all clean fclean re bonus