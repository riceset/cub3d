/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:44:25 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 16:47:31 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_rectangle(t_mlx *img, t_data *data)
{
	t_int_point	start;
	t_int_point	end;
	int			i;
	int			j;

	start.x = data->player->plyr_x + TILE_SIZE * 3 / 8;
	start.y = data->player->plyr_y + TILE_SIZE * 3 / 8;
	end.x = start.x + TILE_SIZE * 2 / 7;
	end.y = start.y + TILE_SIZE * 2 / 7;
	i = start.y;
	while (i < end.y)
	{
		j = start.x;
		while (j < end.x)
		{
			my_mlx_pixel_put(img, j, i, YELLOW);
			j++;
		}
		i++;
	}
}

void	draw_player_fov(t_mlx *img, t_data *data)
{
	double	start_angle;
	double	angle_step;

	start_angle = data->player->angle - data->player->fov_rd / 2;
	angle_step = data->player->fov_rd / 20;
	while (start_angle < data->player->angle + data->player->fov_rd / 2)
	{
		draw_ray_minimap(img, data, start_angle, GREEN);
		start_angle += angle_step;
	}
}

void	draw_player(t_mlx *img, t_data *data)
{
	draw_player_rectangle(img, data);
	draw_player_fov(img, data);
}
