NAME = cub3D

SRC_DIR		=	sources
SRC			=	main.c
SRCS		=	$(addprefix $(SRC_DIR)/, $(SRC))

OBJ_DIR = objects
OBJS := $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

CFLAGS = -Wall -Wextra -Werror -MP -MMD -O3
RM = rm -rf

OBJ_DIR = objects

MLX_DIR = ./libraries/mlx

INC = -I ./includes -I $(MLX_DIR)

ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -DDEBUG
endif

ifeq ($(MAKECMDGOALS), address)
	CFLAGS += -g3 -fsanitize=address
endif

CHECK		= \033[32m[✔]\033[0m
REMOVE		= \033[31m[✘]\033[0m
GENERATE	= \033[33m[➤]\033[0m
BLUE		= \033[1;34m
YELLOW		= \033[1;33m
RESET		= \033[0m

TOTAL_FILES := $(shell echo $(words $(SRCS)))
CURRENT_FILE = 1

define progress
	@printf "$(GENERATE) $(YELLOW)Generating $(NAME) object files: %3d%% (%d/%d)$(RESET)\r" $$(($(CURRENT_FILE)*100/$(TOTAL_FILES))) $(CURRENT_FILE) $(TOTAL_FILES)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@if [ $(CURRENT_FILE) -gt $(TOTAL_FILES) ]; then \
		printf "$(GENERATE) $(YELLOW)Generated $(NAME) object files!%-50.50s\n$(RESET)"; \
	fi
endef

all : $(NAME)

$(NAME): $(OBJS)
	@ $(MAKE) -C $(MLX_DIR)
	@ $(CC) $(CFLAGS) -o $@ $^ -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	@ printf "$(CHECK) $(BLUE)Compiled $(NAME)!%-50.50s\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) $(INC) -o $@ -c $<
	$(call progress)

clean :
	@ $(MAKE) -C $(MLX_DIR) clean
	@ $(RM) $(OBJ_DIR)
	@ echo "$(REMOVE) $(BLUE)Removing $(NAME) object files $(RESET)"

fclean :
	@ $(MAKE) -C $(MLX_DIR) fclean
	@ $(RM) $(OBJ_DIR) $(NAME)
	@ echo "$(REMOVE) $(BLUE)Removing $(NAME) object files and $(NAME) $(RESET)"

re : fclean all

debug : re

address : re

norm :
	norminette sources includes libft

.PHONY : all clean fclean re
