/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:37:10 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 16:48:43 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ray_minimap(t_mlx *img, t_data *data, double angle, int color)
{
	float		ray_length;
	t_int_point	start;
	t_int_point	end;

	ray_length = cast_ray(data, angle);
	end.x = data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7
		+ (int)(ray_length * cos(angle));
	end.y = data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7
		- (int)(ray_length * sin(angle));
	start.x = data->player->plyr_x + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
	start.y = data->player->plyr_y + TILE_SIZE * 3 / 8 + TILE_SIZE / 7;
	draw_line(img, start, end, color);
}
