/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:16:58 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 17:17:32 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	cast_ray_step(float x, float y, float angle, t_data *data);
static int		check_collision(float x, float y, float angle, t_data *data);

float	cast_ray(t_data *data, double angle)
{
	float	x;
	float	y;

	x = data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
	y = data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
	return (cast_ray_step(x, y, angle, data));
}

static float	cast_ray_step(float x, float y, float angle, t_data *data)
{
	float	x_step;
	float	y_step;

	x_step = cos(angle) / 45;
	y_step = -sin(angle) / 45;
	while (x >= 0 && x < data->w_map * TILE_SIZE && y >= 0 && y < data->h_map
		* TILE_SIZE && data->map[(int)(y / TILE_SIZE)][(int)(x
			/ TILE_SIZE)] != WALL)
	{
		x += x_step;
		y += y_step;
		if (check_collision(x, y, angle, data))
			break ;
		if (x < 0 || x >= data->w_map * TILE_SIZE || y < 0 || y >= data->h_map
			* TILE_SIZE)
			break ;
	}
	return (hypot(x - data->player->plyr_x - TILE_SIZE * 3 / 8 - TILE_SIZE / 7,
			y - data->player->plyr_y - TILE_SIZE * 3 / 8 - TILE_SIZE / 7));
}

static int	check_collision(float x, float y, float angle, t_data *data)
{
	int	previous_x;
	int	previous_y;

	previous_x = (int)((x - cos(angle) / 45) / TILE_SIZE);
	previous_y = (int)((y + sin(angle) / 45) / TILE_SIZE);
	if ((previous_x < 0 || previous_y < 0 || previous_x >= data->w_map
			|| previous_y >= data->h_map) || ((int)(x / TILE_SIZE) < 0
		|| (int)(y / TILE_SIZE) < 0 || (int)(x / TILE_SIZE) >= data->w_map
		|| (int)(y / TILE_SIZE) >= data->h_map))
		return (1);
	return (abs((previous_x - (int)(x / TILE_SIZE))) + abs((previous_y - (int)(y
					/ TILE_SIZE))) == 2 && ((data->map[previous_y][(int)(x
					/ TILE_SIZE)] == WALL) || (data->map[(int)(y
					/ TILE_SIZE)][previous_x] == WALL)));
}
