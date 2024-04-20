/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiro <hiro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:40 by tkomeno           #+#    #+#             */
/*   Updated: 2024/04/20 16:58:52 by tkomeno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libraries/ft_printf/ft_printf.h"
# include "../libraries/get_next_line/get_next_line.h"
# include "../libraries/libft/libft.h"
# include "../libraries/mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Operation status codes
# define SUCCESS 0
# define ERROR 1

// Event types
# define ON_KEYDOWN 2
# define ON_DESTROY 17

// Event masks
# define KEY_PRESS_MASK (1L << 0)
# define NO_EVENT_MASK (0L)

// Keyboard key codes
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13

// Game settings
# define ROTATION_SPEED 0.045
# define TILE_SIZE 15

// Window dimensions
# define WIDTH 1200
# define HEIGHT 600

// Colors
# define FLOOR 'F'
# define CEILING 'C'

// Color codes
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GREY 0x808080
# define RED 0xFF0000
# define ASH 0xB2BEB5
# define YELLOW 0xFFFF00
# define GREEN 0x00B16B
# define CORNSILK 0xFFF8DC

typedef struct s_mlx
{
	void			*img;
	char			*addr;
	void			*mlx;
	void			*mlx_win;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_mlx;

typedef struct s_player
{
	int				plyr_x;
	int				plyr_y;
	double			angle;
	float fov_rd; // 既にあるかもしれません
	int				player_status;
}					t_player;

typedef struct s_colors
{
	int				floor_color;
	int				ceiling_color;
}					t_colors;

typedef struct s_data
{
	int				**map;
	int				p_x;
	int				p_y;
	int				w_map;
	int				h_map;
	t_player		*player;
	t_mlx			img;
	t_colors		colors;
}					t_data;

typedef enum e_map_element
{
	FREE_SPACE,
	WALL,
	FORBIDDEN_SPACE,
	PLAYER_NORTH,
	PLAYER_SOUTH,
	PLAYER_EAST,
	PLAYER_WEST,
}					t_map_element;

typedef struct s_texture
{
	unsigned char	*data;
	int				height;
	int				width;
}					t_texture;

t_data				*init_data(char **argv);
void				ft_exit(char *err_msg, t_data *data);
void				print_file(char *filename);
void				print_map(int **map, int w_map, int h_map);
int					extension_check(char *filename);
void				update_graphics(t_data *data);
void				draw_minimap(t_data *data, t_mlx img);
void				start_game(t_data *data);
t_player			*init_player(t_data *data);
int					get_map_width(char *filename, t_data *data);
int					get_map_height(char *filename, t_data *data);
int					**init_map(char *filename, int h_map, int w_map,
						t_data *data);
int					validate_map(t_data *data);
void				draw_square(t_mlx *img, int start_x, int start_y, int color,
						int size);
void				draw_grid(t_mlx *img, int x, int y, int color, int size);
void				draw_player(t_mlx *img, t_data *data);
void				draw_line(t_mlx *img, int start_x, int start_y, int end_x,
						int end_y, int color);
int					open_file(const char *filename, t_data *data);
int					num_count(char *str);
void				free_array(char **array);
int					rgb_to_int(int r, int g, int b);
int					check_line(char *line);
void				render_wall(t_data *data, t_mlx *img);
void				fill_map_row(int *map_row, char *line, int w_map,
						t_data *data);
int					**allocate_map_memory(int h_map, int w_map, t_data *data);
int					get_map_colors(char *filename, t_data *data, char type);
void flood_fill(int **map, int x, int y, int h_map, int w_map, int *status);
int **copy_map(int **src, int h_map, int w_map);
int close_window(void *param);
int key_press(int keycode, t_data *data);
int is_hitting_wall(float player_center_x, float player_center_y, t_data *data);
double init_angle(t_player *player);
t_player *init_player(t_data *data);

#endif
