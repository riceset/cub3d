/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:43:23 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 20:00:40 by riceset          ###   ########.fr       */
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

# define TRUE 0
# define FALSE 1

// Event types
# define ON_KEYDOWN 2
# define ON_DESTROY 17

// Event masks
# define KEY_PRESS_MASK (1L)
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
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

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

typedef struct s_int_point
{
	int					x;
	int					y;
}						t_int_point;

typedef struct s_float_point
{
	float				x;
	float				y;
}						t_float_point;

typedef struct s_mlx
{
	void				*img;
	char				*addr;
	void				*mlx;
	void				*mlx_win;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_mlx;

typedef struct s_player
{
	int					plyr_x;
	int					plyr_y;
	double				angle;
	float				fov_rd;
	int					player_status;
}						t_player;

typedef struct s_colors
{
	int					floor_color;
	int					ceiling_color;
}						t_colors;

typedef struct s_data
{
	int					**map;
	int					p_x;
	int					p_y;
	int					w_map;
	int					h_map;
	t_player			*player;
	t_mlx				img;
	t_colors			colors;
	char				*texture[4];
}						t_data;

typedef enum e_map_element
{
	FREE_SPACE,
	WALL,
	FORBIDDEN_SPACE,
	PLAYER_NORTH,
	PLAYER_SOUTH,
	PLAYER_EAST,
	PLAYER_WEST,
}						t_map_element;

typedef struct s_texture
{
	unsigned char		*data;
	int					height;
	int					width;
}						t_texture;

typedef struct s_wall_data
{
	int					top_pixel;
	int					bottom_pixel;
	int					wall_height;
	float				distance;
}						t_wall_data;

typedef struct s_texture_data
{
	double				hit_x;
	double				hit_y;
	double				wall_x;
	int					tex_x;
	t_texture			*texture[4];
}						t_texture_data;

typedef struct s_wall_tex_data
{
	t_wall_data			wall_data;
	t_texture_data		tex_data;
}						t_wall_tex_data;

void					render_wall(t_data *data, t_mlx *img);
float					calculate_ray_distance(t_data *data, int ray);
void					draw_ceiling_floor(t_data *data, t_mlx *img, int ray,
							t_wall_data *wall_data);
void					fill_wall_data(t_wall_data *wall_data, float distance,
							t_data *data);
void					load_textures(t_data *data, t_texture *textures[4]);
void					free_textures(t_texture *textures[4]);
float					cast_ray(t_data *data, double angle);
void					flood_fill(int **map, t_int_point point, t_data *data,
							int *status);
void					update_graphics(t_data *data);
void					start_game(t_data *data);
int						validate_map(t_data *data);
t_texture				*load_texture_from_bmp(const char *file_path);
int						bytes_to_int(unsigned char *bytes, int num_bytes);
void					read_bmp_header(int fd, int *width, int *height,
							int *has_alpha);
int						open_texture_file(const char *file_path);
t_texture				*allocate_texture(void);
void					read_and_validate_header(int fd, t_texture *texture,
							int *has_alpha);
void					draw_minimap(t_data *data, t_mlx img);
void					draw_square(t_mlx *img, t_int_point start, int color,
							int size);
void					draw_grid(t_mlx *img, t_int_point p, int color,
							int size);
void					draw_player(t_mlx *img, t_data *data);
void					draw_line(t_mlx *img, t_int_point start,
							t_int_point end, int color);
void					draw_ray_minimap(t_mlx *img, t_data *data, double angle,
							int color);
void					draw_textured_wall(t_mlx *img, int ray,
							t_wall_tex_data *walltex, t_data *data);
t_data					*init_data(char **argv);
t_player				*init_player(t_data *data);
int						**init_map(char *filename, t_data *data);
double					init_angle(t_player *player);
int						get_map_width(char *filename, t_data *data);
int						get_map_height(char *filename, t_data *data);
int						get_map_colors(char *filename, t_data *data, char type);
int						get_texture_color(t_texture *texture, int x, int y);
char					**get_textures(char *filename, t_data **data);
void					ft_exit(char *err_msg, t_data *data);
void					print_file(char *filename);
void					print_map(int **map, int w_map, int h_map);
int						extension_check(char *filename);
int						num_count(char *str);
int						open_file(const char *filename, t_data *data);
void					free_array(char **array);
int						rgb_to_int(int r, int g, int b);
int						check_line(char *line);
int						**allocate_map_memory(t_data *data);
int						**copy_map(int **src, int h_map, int w_map);
int						determine_wall_direction(t_data *data,
							double ray_angle);
void					fill_map_row(int *map_row, char *line, t_data *data);
int						close_window(void *param);
int						key_press(int keycode, t_data *data);
int						is_hitting_wall(float player_center_x,
							float player_center_y, t_data *data);
void					my_mlx_pixel_put(t_mlx *img, int x, int y, int color);
char					*extract_filename(char *path);
void					free_data(t_data *data);
int						is_direction_map(int data);
float					calculate_initial_position(float player_position,
							int tile_size);
float					calculate_step(double angle, int is_x_step);
void					free_textures(t_texture *textures[4]);
void					load_textures(t_data *data, t_texture *textures[4]);
void					draw_floor(t_mlx *img, int ray, int top_pixel,
							int color);
void					draw_ceiling(t_mlx *img, int ray, int bottom_pixel,
							int color);
void					calculate_hits_and_texture(t_data *data,
							double ray_angle, int direction,
							t_texture_data *tex_data);
int						get_direction(t_data *data, int ray,
							t_texture_data *tex_data);
void					draw_textured_pixels(t_mlx *img, int ray, int direction,
							t_wall_tex_data *walltex);
void					handle_east(t_data *data, double distance,
							double ray_angle, t_texture_data *tex_data);
void					handle_west(t_data *data, double distance,
							double ray_angle, t_texture_data *tex_data);
void					handle_south(t_data *data, double distance,
							double ray_angle, t_texture_data *tex_data);
void					handle_north(t_data *data, double distance,
							double ray_angle, t_texture_data *tex_data);

#endif
