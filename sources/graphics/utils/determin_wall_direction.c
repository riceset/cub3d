/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determin_wall_direction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:17:43 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 18:55:58 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_out_of_bounds(t_float_point p, t_data *data)
{
	return (p.x < 0 || p.x >= data->w_map * TILE_SIZE || p.y < 0
		|| p.y >= data->h_map * TILE_SIZE);
}

int	detect_collision(t_int_point curr, t_int_point prev, t_float_point step,
		t_data *data)
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
	return (0);
}

int	trace_ray(t_data *data, t_float_point p, t_float_point step)
{
	t_int_point	prev;
	t_int_point	curr;
	int			result;

	prev.x = (int)(p.x / TILE_SIZE);
	prev.y = (int)(p.y / TILE_SIZE);
	while (!is_out_of_bounds(p, data) && data->map[(int)(p.y
			/ TILE_SIZE)][(int)(p.x / TILE_SIZE)] != WALL)
	{
		p.x += step.x;
		p.y += step.y;
		curr.x = (int)(p.x / TILE_SIZE);
		curr.y = (int)(p.y / TILE_SIZE);
		if (curr.y >= 0 && curr.y < data->h_map && curr.x >= 0
			&& curr.x < data->w_map)
		{
			result = detect_collision(curr, prev, step, data);
			if (result)
				return (result);
		}
		prev = curr;
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
