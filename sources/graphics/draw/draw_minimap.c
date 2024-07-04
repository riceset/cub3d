/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:43:41 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 16:55:40 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap(t_data *data, t_mlx img)
{
	t_int_point	p;
	int			color;

	p.x = 0;
	p.y = 0;
	while (p.y < data->h_map)
	{
		p.x = 0;
		while (p.x < data->w_map)
		{
			if (data->map[p.y][p.x] == WALL
				|| data->map[p.y][p.x] == FORBIDDEN_SPACE)
			{
				if (data->map[p.y][p.x] == WALL)
					color = WHITE;
				else if (data->map[p.y][p.x] == FORBIDDEN_SPACE)
					color = RED;
				draw_square(&img, p, color, TILE_SIZE);
			}
			draw_grid(&img, p, GREY, TILE_SIZE);
			if (data->map[p.y][p.x] >= PLAYER_NORTH
				&& data->map[p.y][p.x] <= PLAYER_WEST)
				draw_player(&img, data);
			(p.x)++;
		}
		(p.y)++;
	}
	mlx_put_image_to_window(data->img.mlx, data->img.mlx_win, data->img.img, 0,
		0);
}
