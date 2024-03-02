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

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@
	@ echo "$(GENERATE) $(YELLOW)Compiling libft: $< $(RESET)"

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