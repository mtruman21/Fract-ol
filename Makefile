# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mtruman <mtruman@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/02 12:10:11 by mtruman           #+#    #+#              #
#    Updated: 2019/09/10 17:32:44 by mtruman          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

HEADER = ./includes/fractol.h

SRC =$(NAME).c\
				tools.c\
				julia.c\
				mandelbrot.c\
				brain.c\
				controls.c\
				render.c\
				burning_ship.c\
		
OBJ	= $(addprefix $(OBJDIR),$(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -o3

MLX = ./minilibx_macos/
MLX_LIB	= $(addprefix $(MLX),mlx.a)
MLX_INC	= -I ./minilibx_macos
MLX_LNK	= -L ./minilibx_macos -l mlx -framework OpenGL -framework AppKit

FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

SRCDIR	= ./sources/
INCDIR	= ./includes/
OBJDIR	= ./obj/

GREEN= \033[0;32m
RED= \033[0;031m
RESET= \033[0m

all: obj $(FT_LIB) $(MLX_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c $(HEADER)
	@$(CC) $(CFLAGS) $(MLX_INC) $(FT_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

$(MLX_LIB):
	@make -C $(MLX)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLX_LNK) $(FT_LNK) -lm -o $(NAME)
	@echo "\n$(NAME): $(GREEN) object files were created $(RESET)"
	@echo "$(NAME): $(GREEN) $(NAME) was created $(RESET)"

clean:
	@rm -rf $(OBJDIR)
	@make -C $(FT) clean
	@make -C $(MLX) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(FT) fclean

re: 
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: clean fclean all re
