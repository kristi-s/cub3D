cmake_minimum_required(VERSION 3.16)
project(cub3D C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(minilibx_mms_20200219)
include_directories(libft)
include_directories(get_next_line)
include_directories(includes)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -L. -lmlx -framework OpenGL -framework AppKit")

file(GLOB
        LIBFT "libft/*.c")
file(GLOB
        SRCS "*.c")

add_executable(cub3D
        ${LIBFT}
        ${SRCS}
        main.c valid_map.c)
