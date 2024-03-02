NAME = cub3D

SRC_DIR = sources
OBJ_DIR = objects

MLX_DIR = ./libraries/mlx
GNL_DIR = ./libraries/get_next_line
FT_PRINTF_DIR = ./libraries/ft_printf

SRC = main.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

GNL_SRC = get_next_line.c get_next_line_utils.c
FT_PRINTF_SRC = ft_printf.c ft_putnbr.c ft_strlen.c ft_putchar_printf.c ft_putstr_printf.c ft_putnbr_p.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
       $(GNL_SRC:%.c=$(OBJ_DIR)/%.o) \
       $(FT_PRINTF_SRC:%.c=$(OBJ_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror -MP -MMD -O3
RM = rm -rf

INC = -I ./includes -I $(MLX_DIR) -I $(GNL_DIR) -I $(FT_PRINTF_DIR)

ifeq ($(MAKECMDGOALS), debug)
    CFLAGS += -DDEBUG
endif

ifeq ($(MAKECMDGOALS), address)
    CFLAGS += -g3 -fsanitize=address
endif

CHECK = \033[32m[✔]\033[0m
REMOVE = \033[31m[✘]\033[0m
GENERATE = \033[33m[➤]\033[0m
BLUE = \033[1;34m
YELLOW = \033[1;33m
RESET = \033[0m

TOTAL_FILES := $(shell echo $(words $(SRCS) $(GNL_SRC) $(FT_PRINTF_SRC)))
CURRENT_FILE = 1

define progress
    @printf "$(GENERATE) $(YELLOW)Generating $(NAME) object files: %3d%% (%d/%d)$(RESET)\r" $$(($(CURRENT_FILE)*100/$(TOTAL_FILES))) $(CURRENT_FILE) $(TOTAL_FILES)
    @$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
    @if [ $(CURRENT_FILE) -gt $(TOTAL_FILES) ]; then \
        printf "$(GENERATE) $(YELLOW)Generated $(NAME) object files!%-50.50s\n$(RESET)"; \
    fi
endef

all: $(NAME)

$(NAME): $(OBJS)
	@ $(MAKE) -C $(MLX_DIR)
	@ $(CC) $(CFLAGS) -o $@ $^ -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	@ printf "$(CHECK) $(BLUE)Compiled $(NAME)!%-50.50s\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $(INC) -o $@ -c $<
	$(call progress)

$(OBJ_DIR)/%.o: $(GNL_DIR)/%.c
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@
	@ echo "$(GENERATE) $(YELLOW)Compiling GNL: $< $(RESET)"

$(OBJ_DIR)/%.o: $(FT_PRINTF_DIR)/%.c
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@
	@ echo "$(GENERATE) $(YELLOW)Compiling ft_printf: $< $(RESET)"

clean:
	@ $(MAKE) -C $(MLX_DIR) clean
	@ $(RM) $(OBJ_DIR)
	@ echo "$(REMOVE) $(BLUE)Removing $(NAME) object files $(RESET)"

fclean:
	@ $(MAKE) -C $(MLX_DIR) fclean
	@ $(RM) $(OBJ_DIR) $(NAME)
	@ echo "$(REMOVE) $(BLUE)Removing $(NAME) object files and $(NAME) $(RESET)"

re: fclean all

debug: re

address: re

norm:
	norminette sources includes libft

.PHONY: all clean fclean re
