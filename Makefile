# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cschmied <cschmied@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/19 10:38:26 by cschmied          #+#    #+#              #
#    Updated: 2023/03/05 23:21:39 by cschmied         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      := gcc
CFLAGS  :=  -Wall -Wextra -Werror -I /usr/X11/include -O2
LDFLAGS :=  -I /usr/X11/include -L /usr/X11/lib -lX11 \
			-lmlx -lXext -lm -framework OpenGL -framework AppKit

SRCS    :=  fractol_calculations.c fractol_inits.c fractol_main.c \
			fractol_mouse_events.c fractol_key_events.c fractol_no_event.c \
			fractol_draw.c fractol_colors.c fractol_utils_custom.c \
			fractol_utils_ato.c fractol_utils_str.c
OBJS    := $(SRCS:.c=.o)

NAME    := fractol

VPATH 	:= sources sources/utils

.PHONY: all clean fclean re

MLX = libmlx.a

MAKE = make

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $^ $(LDFLAGS) -o $@
	@echo "\033[1;32m                finished compiling."
	@echo " "
	@echo "\033[1;34mUse ./fractol to run the progam[0m"

$(OBJS): %.o: %.c $(MLX)
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	@echo "\033[1;31mcompiling"
	@$(MAKE) -C mlx all >/dev/null 2>&1
	@cp mlx/$(MLX) .
	@echo "\033[1;31m        ..."
	@echo "\033[1;33m            ..."

clean:
	@rm -f $(OBJS)
	@rm -f $(MLX)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(MLX)

re: fclean all
