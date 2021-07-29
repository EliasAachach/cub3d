# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/24 14:08:36 by elaachac          #+#    #+#              #
#    Updated: 2021/07/29 11:07:43 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
INCLUDE =	cub3d.h\

INC_PATH = ./includes/

vpath %.c srcs/utils
vpath %.c srcs/parsing
vpath %.c srcs/parsing/gnl
vpath %.c srcs/raycasting

FILES =	./srcs/parsing/main\
		./srcs/parsing/checkers\
		./srcs/parsing/check_flag\
		./srcs/parsing/find_map\
		./srcs/parsing/find_map2\
		./srcs/parsing/get_elems\
		./srcs/parsing/get_elems_end\
		./srcs/parsing/flood_fill\
		./srcs/parsing/parsing\
		./srcs/parsing/error\
		./srcs/parsing/get_path\
		./srcs/parsing/valid_map\
		./srcs/parsing/gnl/get_next_line\
		./srcs/parsing/gnl/get_next_line_utils\
		./srcs/utils/utils\
		./srcs/utils/utils2\
		./srcs/utils/utils3\
		./srcs/utils/utils4\
		./srcs/raycasting/raycasting\
		./srcs/raycasting/move\
		./srcs/raycasting/move2\

SRCS = $(addsuffix .c, $(FILES))
OBJ = $(SRCS:.c=.o)

L_CC = clang
FLAGS = -Wall -Wextra -Werror
L_LIB = -lmlx -lXext -lX11 -lm -lbsd -g -fsanitize=address

### COLORS ###

NOC = \033[0m
BOLD = \033[1m
UNDERLINE = \033[4m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
VIOLET = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m

all: 		 $(NAME)

$(NAME): 	$(OBJ)
			@echo "$(CYAN)Constructing executable:$(WHITE) $@"
			@$(L_CC) $(FLAGS) -o $(NAME) $(OBJ) $(L_LIB)
.c.o:		${SRCS}
			@echo " $(VIOLET)[$(L_CC)] $(GREEN)[$(FLAGS)]$(NOC) $(YELLOW)in progress ...:$(NOC) $< $(RED)->$(NOC) $@"
			@$(L_CC) -c -I$(INC_PATH) $< -o ${<:.c=.o}
clean:
	@echo "$(RED)Removing '.o' objects: $(NOC) $@\n"
	@rm -f $(OBJ)

fclean: clean
	@echo "$(RED)Removing executable: $(NOC) $@\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean re fclean

