# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 20:58:17 by droslyn           #+#    #+#              #
#    Updated: 2021/03/19 01:43:30 by droslyn          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
LIBFT = ./libft
SRCS = action.c begin.c copy_map.c draw.c ft_error.c main.c paint_texture.c \
		read_map.c sprites.c valid_map.c create_screenshot.c utility.c \
		hooks.c floor_ceiling_color.c check_texture.c
OBJS = ${SRCS:.c=.o}
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit
# -L.

.c.o:
		${CC} ${CFLAGS} -Imlx -I./ -c $< -o $@

#%.o: %.c cub3D.h
#	${CC} ${CFLAGS} -Imlx -c $< -o $@
# $(NAME): $(OBJ)
#     $(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

${NAME}: ${OBJS}
#		${MAKE} -C ./mlx
#		cp mlx/libmlx.dylib ./
		${MAKE} -C ./libft
		${CC} ${OBJS} -I. -I./mlx ${CFLAGS} ${MLX} ./libft/libft.a -o ${NAME}

all:	${NAME}

clean:
		${RM} ${OBJS}
		${MAKE} fclean -C ${LIBFT}

fclean:	clean
		${RM} ${NAME}
		${RM} libft.a

re:		fclean all

main: re
	gcc main.c ${NAME}

.PHONY:	bonus all clean fclean re
