/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:11:42 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/04 11:39:52 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_data *data, t_mlx img)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->h_map)
	{
		x = 0;
		while (x < data->w_map)
		{
			draw_square(&img, x * TILE_SIZE, y * TILE_SIZE, BLACK, TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	draw_element(t_mlx *img, int x, int y, int type)
{
	int	color;

	if (type == WALL)
	{
		color = WHITE;
		draw_square(img, x * TILE_SIZE, y * TILE_SIZE, color, TILE_SIZE);
	}
	else if (type == FORBIDDEN_SPACE)
	{
		color = RED;
		draw_square(img, x * TILE_SIZE, y * TILE_SIZE, color, TILE_SIZE);
	}
}

void	draw_elements(t_data *data, t_mlx img)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->h_map)
	{
		x = 0;
		while (x < data->w_map)
		{
			if (data->map[y][x] == WALL || data->map[y][x] == FORBIDDEN_SPACE)
				draw_element(&img, x, y, data->map[y][x]);
			if (data->map[y][x] >= PLAYER_NORTH
				&& data->map[y][x] <= PLAYER_WEST)
				draw_player(&img, data);
			draw_grid(&img, x, y, TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_data *data, t_mlx img)
{
	draw_background(data, img);
	draw_elements(data, img);
	mlx_put_image_to_window(data->img.mlx, data->img.mlx_win, data->img.img, 0,
		0);
}
