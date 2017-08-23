# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/18 04:37:02 by fcecilie          #+#    #+#              #
#    Updated: 2017/08/16 15:49:12 by fcecilie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

SRC = main.c \
	  parsing.c \
	  parsing_camera.c \
	  parsing_objects.c \
	  parsing_lights.c \
	  get_objects_informations.c \
	  get_lights_informations.c \
	  attribution.c \
	  heart.c \
	  dist_camera_obj.c \
	  dist_camera_lux.c \
	  display.c \
	  key.c \
	  utils.c \
	  matrice.c \
	  math.c \
	  brackets.c \
	  get_file_to_string.c \
	  get_string_interval.c \
	  plan.c \
	  sphere.c \
	  cone.c \
	  cylindre.c \

SRC := $(addprefix sources/, $(SRC))

OBJ = $(SRC:.c=.o)

# ================================= #

FLAGS = -Wall -Wextra -Werror

FLAGS_MLX = -lmlx -framework OpenGL -framework AppKit

MLX = -L minilibx -lmlx

FT = -L libft/ -lft

# ================================= #

all: $(NAME)

$(NAME): libft minilibx $(OBJ)
	$(CC) $(FLAGS) $(FLAGS_MLX) $(FT) $(MLX) -o $(NAME) $(OBJ) 

%.o: %.c includes/rtv1.h
	$(CC) $(FLAGS) -o $@ -c $< -I includes/

libft:
	make -C libft/

minilibx:
	make -C minilibx/

clean:
	rm -rf $(OBJ)
	rm -rf libft/sources/*.o
	rm -rf minilibx/*.o

fclean: clean
	rm -rf $(NAME)
	rm -rf libft/libft.a
	rm -rf minilibx/libmlx.a

re: fclean all

.PHONY: libft minilibx
