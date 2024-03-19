/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiro <hiro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:40 by tkomeno           #+#    #+#             */
/*   Updated: 2024/03/19 19:55:16 by hiro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libraries/libft/libft.h"
#include "../libraries/mlx/mlx.h"
#include "../libraries/get_next_line/get_next_line.h"
#include "../libraries/ft_printf/ft_printf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Operation status codes
#define SUCCESS 0
#define ERROR 1

// Event types
#define ON_KEYDOWN 2

// Event masks
#define KEY_PRESS_MASK (1L<<0)

// Keyboard key codes
#define KEY_ESC 53
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13

// Game settings
#define ROTATION_SPEED 0.045
#define TILE_SIZE 15

// Window dimensions
#define WIDTH 1200
#define HEIGHT 600

// Color codes
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define GREY 0x808080
#define RED 0xFF0000
#define ASH 0xB2BEB5
#define YELLOW 0xFFFF00
#define GREEN 0x00B16B
#define CORNSILK 0xFFF8DC

typedef struct s_mlx
{
	void *img;
	char *addr;
	void *mlx;
	void *mlx_win;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_mlx;

typedef struct s_player
{
	int plyr_x;
	int plyr_y;
	double angle;
	float fov_rd;
	int player_status;
} t_player;

typedef struct s_data
{
	int **map;
	int p_x;
	int p_y;
	int w_map;
	int h_map;
	t_player *player;
	t_mlx img;
} t_data;

typedef enum e_map_element
{
	FREE_SPACE,
	WALL,
	FORBIDDEN_SPACE,
	PLAYER_NORTH,
	PLAYER_SOUTH,
	PLAYER_EAST,
	PLAYER_WEST,
} t_map_element;

t_data *init_data(char **argv);
void ft_exit(char *err_msg, t_data *data);
void print_file(char *filename);
void print_map(int **map, int w_map);
int	extension_check(char *filename);
void update_graphics(t_data *data);
void draw_minimap(t_data *data, t_mlx img);
void start_game(t_data *data);
t_player *init_player(t_data *data);
int get_width(char *filename, t_data *data);
int get_height(char *filename, t_data *data);
int **init_map(char *filename, int h_map, int w_map, t_data *data);
int validate_map(t_data *data);
void draw_square(t_mlx *img, int start_x, int start_y, int color, int size);
void draw_grid(t_mlx *img, int x, int y, int color, int size);
void draw_player(t_mlx *img, t_data *data);
void draw_line(t_mlx *img, int start_x, int start_y, int end_x, int end_y, int color);
int open_file(char *filename);
int num_count(char *str);

#endif
