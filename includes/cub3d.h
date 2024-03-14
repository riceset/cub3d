/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiro <hiro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:39:40 by tkomeno           #+#    #+#             */
/*   Updated: 2024/03/13 17:20:51 by hiro             ###   ########.fr       */
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

#define SUCCESS 0
#define ERROR 1
#define KEY_ESC 53

#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define GREY 0x808080
#define RED 0xFF0000
#define ASH 0xB2BEB5
#define YELLOW 0xFFFF00
#define GREEN 0x00B16B

#define TILE_SIZE 30

#define WIDTH 1200
#define HEIGHT 600


typedef struct s_mlx
{
	void *img;
	char *addr;
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

#endif
