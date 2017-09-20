# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edeveze <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 18:25:38 by edeveze           #+#    #+#              #
#    Updated: 2017/09/20 18:25:41 by edeveze          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME = edeveze.filler

# Sources
SRC =	encircle.c\
		find_place.c\
		going_edge.c\
		going_mid.c\
		going_opp_direction.c\
		main.c\
		positions.c\

# Includes
INC = -I includes -I libft/includes

# Objects
OBJ = $(SRC:.c=.o)

# Compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror
PRGFLAGS = -L libft/ libft/libft.a

# Colors
PURPLE = \033[1;35m
RED = \033[0;31m
NC = \033[0m

# Rules

all : lib $(NAME)

lib:
	@make -C libft

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(PRGFLAGS) -o $@ $(OBJ)
	@echo "$(PURPLE) ______   __     __         __         ______     ______ "   
	@echo "/\  ___\ /\ \   /\ \       /\ \       /\  ___\   /\  == \   "
	@echo "\ \  __\ \ \ \  \ \ \____  \ \ \____  \ \  __\   \ \  __<   "
	@echo " \ \_\    \ \_\  \ \_____\  \ \_____\  \ \_____\  \ \_\ \_\ "
	@echo "  \/_/     \/_/   \/_____/   \/_____/   \/_____/   \/_/ /_/ $(NC)"
                                                            

%.o: %.c libft/libft.a
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	@rm -rf $(OBJ)
	@make -C libft clean

fclean : clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@echo "$(RED)---filler removed completely---$(NC)"

re : fclean all

.PHONY: all clean fclean re