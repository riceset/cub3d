SRCS = $(shell find $(SRC_DIR) -type f -name '*.c')

GNL_SRC = get_next_line.c \
		  get_next_line_utils.c

FT_PRINTF_SRC = ft_printf.c \
				ft_putnbr.c \
				ft_strlen.c \
				ft_putchar_printf.c \
				ft_putstr_printf.c \
				ft_putnbr_p.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
       $(GNL_SRC:%.c=$(OBJ_DIR)/%.o) \
       $(FT_PRINTF_SRC:%.c=$(OBJ_DIR)/%.o)