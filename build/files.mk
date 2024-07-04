SRCS = sources/game/hooks/utils/is_hitting_wall.c \
sources/game/hooks/close_window.c \
sources/game/hooks/handle_key.c \
sources/game/hooks/key_press.c \
sources/game/start_game.c \
sources/graphics/bmp/helpers.c \
sources/graphics/bmp/load_texture_from_bmp.c \
sources/graphics/draw/calculate_direction.c \
sources/graphics/draw/draw_grid.c \
sources/graphics/draw/draw_line.c \
sources/graphics/draw/draw_minimap.c \
sources/graphics/draw/draw_player.c \
sources/graphics/draw/draw_ray_minimap.c \
sources/graphics/draw/draw_square.c \
sources/graphics/draw/draw_textured_wall.c \
sources/graphics/draw/draw_wall.c \
sources/graphics/draw/render_wall.c \
sources/graphics/draw/textures.c \
sources/graphics/utils/calculate.c \
sources/graphics/utils/cast_ray.c \
sources/graphics/utils/determin_wall_direction.c \
sources/graphics/utils/extract_filename.c \
sources/graphics/utils/get_texture_color.c \
sources/graphics/utils/my_mlx_pixel_put.c \
sources/graphics/utils/update_graphics.c \
sources/initialize/get_map_colors/get_map_colors.c \
sources/initialize/get_map_dimensions/utils/num_count.c \
sources/initialize/get_map_dimensions/get_map_height.c \
sources/initialize/get_map_dimensions/get_map_width.c \
sources/initialize/get_textures/get_textures.c \
sources/initialize/init_map/utils/allocate_map_memory.c \
sources/initialize/init_map/utils/fill_map_row.c \
sources/initialize/init_map/init_map.c \
sources/initialize/init_player/utils/init_angle.c \
sources/initialize/init_player/utils/is_direction_map.c \
sources/initialize/init_player/init_player.c \
sources/initialize/validate_map/utils/copy_map.c \
sources/initialize/validate_map/utils/flood_fill.c \
sources/initialize/validate_map/validate_map.c \
sources/initialize/init_data.c \
sources/utils/utils.c \
sources/utils/utils_free.c \
sources/utils/utils_print.c \
sources/main.c

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
