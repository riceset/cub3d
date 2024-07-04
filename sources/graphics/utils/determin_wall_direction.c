/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determin_wall_direction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:17:43 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 17:23:40 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calculate_initial_position(float player_position, int tile_size)
{
	return (player_position + tile_size * 3 / 8 + tile_size / 7);
}

float	calculate_step(double angle, int is_x_step)
{
	float	result;

	if (is_x_step)
		result = cos(angle) / 45;
	else
		result = -sin(angle) / 45;
	return (result);
}

int	trace_ray(t_data *data, t_float_point p, t_float_point step)
{
	t_int_point	prev;
	t_int_point	curr;

	prev.x = (int)(p.x / TILE_SIZE);
	prev.y = (int)(p.y / TILE_SIZE);
	while (data->map[(int)(p.y / TILE_SIZE)][(int)(p.x / TILE_SIZE)] != WALL)
	{
		p.x += step.x;
		p.y += step.y;
		if (p.x < 0 || p.x >= data->w_map * TILE_SIZE || p.y < 0
			|| p.y >= data->h_map * TILE_SIZE)
			break ;
		curr.x = (int)(p.x / TILE_SIZE);
		curr.y = (int)(p.y / TILE_SIZE);
		if (curr.y >= 0 && curr.y < data->h_map && curr.x >= 0
			&& curr.x < data->w_map)
		{
			if (data->map[curr.y][curr.x] == WALL)
			{
				if (curr.x != prev.x)
				{
					if (step.x > 0)
						return (WEST);
					else
						return (EAST);
				}
				else if (curr.y != prev.y)
				{
					if (step.y > 0)
						return (NORTH);
					else
						return (SOUTH);
				}
			}
		}
		prev.x = curr.x;
		prev.y = curr.y;
	}
	return (0);
}

int	determine_wall_direction(t_data *data, double ray_angle)
{
	t_float_point	p;
	t_float_point	step;

	p.x = calculate_initial_position(data->player->plyr_x, TILE_SIZE);
	p.y = calculate_initial_position(data->player->plyr_y, TILE_SIZE);
	step.x = calculate_step(ray_angle, 1);
	step.y = calculate_step(ray_angle, 0);
	return (trace_ray(data, p, step));
}
