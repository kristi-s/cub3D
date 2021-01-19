# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: droslyn <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/30 20:58:17 by droslyn           #+#    #+#              #
#    Updated: 2020/11/30 16:10:06 by droslyn          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
# LIBFT = ./libft
# SRCS = ft_printf.c ft_printf_utils.c ft_write_hex.c ft_write_int.c \
		ft_write_ptr.c ft_write_str.c ft_write_char.c
OBJS = ${SRCS:.c=.o}
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -Ilibft/ -I./ -c $< -o $@

# %.o: %.c
#       $(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
# $(NAME): $(OBJ)
#     $(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

${NAME}: ${OBJS}
		${MAKE} -C ${LIBFT}
		cp ./libft/libft.a ./${NAME}
		ar rcs ${NAME} ${OBJS}

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
