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
	float			fov_rd;
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
	char			*texture[4];
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

typedef struct s_wall_data
{
	int				top_pixel;
	int				bottom_pixel;
	int				wall_height;
	float			distance;
}					t_wall_data;

typedef struct s_texture_data
{
	double			hitX;
	double			hitY;
	double			wallX;
	int				texX;
	t_texture		*texture[4];
}					t_texture_data;

// cub3d
void				render_wall(t_data *data, t_mlx *img);
float				cast_ray(t_data *data, double angle);
void				render_wall(t_data *data, t_mlx *img);
void				flood_fill(int **map, int x, int y, int h_map, int w_map,
						int *status);
void				update_graphics(t_data *data);
void				start_game(t_data *data);
int					validate_map(t_data *data);
t_texture			*load_texture_from_bmp(const char *file_path);
void				update_graphics(t_data *data);

// draw
void				draw_minimap(t_data *data, t_mlx img);
void				draw_square(t_mlx *img, int start_x, int start_y, int color,
						int size);
void				draw_grid(t_mlx *img, int x, int y, int size);
void				draw_player(t_mlx *img, t_data *data);
void				draw_line(t_mlx *img, int start_x, int start_y, int end_x,
						int end_y, int color);
void				draw_line(t_mlx *img, int start_x, int start_y, int end_x,
						int end_y, int color);
void				draw_square(t_mlx *img, int start_x, int start_y, int color,
						int size);
void				draw_player(t_mlx *img, t_data *data);
void				draw_ray_minimap(t_mlx *img, t_data *data, double angle,
						int color);
void				draw_minimap(t_data *data, t_mlx img);
void				draw_textured_wall(t_mlx *img, int ray,
						t_wall_data *wall_data, t_texture_data *tex_data,
						t_data *data);
void				draw_wall(t_mlx *img, int ray, int top_pixel,
						int bottom_pixel, int color);

// init
t_data				*init_data(char **argv);
t_player			*init_player(t_data *data);
int					**init_map(char *filename, int h_map, int w_map,
						t_data *data);
double				init_angle(t_player *player);
t_player			*init_player(t_data *data);

// getter
int					get_map_width(char *filename, t_data *data);
int					get_map_height(char *filename, t_data *data);
int					get_map_colors(char *filename, t_data *data, char type);
int					get_texture_color(t_texture *texture, int x, int y);
char				**get_textures(char *filename, t_data **data);

// utils
void				ft_exit(char *err_msg, t_data *data);
void				print_file(char *filename);
void				print_map(int **map, int w_map, int h_map);
int					extension_check(char *filename);
int					num_count(char *str);
int					open_file(const char *filename, t_data *data);
void				free_array(char **array);
int					rgb_to_int(int r, int g, int b);
int					check_line(char *line);
int					**allocate_map_memory(int h_map, int w_map, t_data *data);
int					**copy_map(int **src, int h_map, int w_map);
int					determine_wall_direction(t_data *data, double ray_angle);
void				fill_map_row(int *map_row, char *line, int w_map,
						t_data *data);
int					close_window(void *param);
int					key_press(int keycode, t_data *data);
int					is_hitting_wall(float player_center_x,
						float player_center_y, t_data *data);
void				my_mlx_pixel_put(t_mlx *img, int x, int y, int color);
char				*extract_filename(char *path);
void				free_data(t_data *data);
int					is_direction_map(int data);

#endif
