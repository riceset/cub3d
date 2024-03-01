NAME = cub3d
CC = cc
RM = rm -rf
MKDIR = mkdir -p
INCLUDES = -I ./includes
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

FILES = main.c

SRC_DIR 	= sources
OBJ_DIR		= objects

SRCS		=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean:
	$(RM) $(OBJ_DIR) $(NAME)

re: fclean all

.PHONY: all clean fclean re
