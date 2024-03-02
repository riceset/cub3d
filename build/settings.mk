NAME = cub3D

SRC_DIR = sources
OBJ_DIR = objects

MLX_DIR = ./libraries/mlx
GNL_DIR = ./libraries/get_next_line
FT_PRINTF_DIR = ./libraries/ft_printf
LIBFT_DIR = ./libraries/libft

CFLAGS = -Wall -Wextra -Werror -MP -MMD -O3

RM = rm -rf

INC = -I ./includes -I $(MLX_DIR) -I $(GNL_DIR) -I $(FT_PRINTF_DIR) -I ${LIBFT_DIR}