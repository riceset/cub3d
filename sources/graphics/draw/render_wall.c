/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:58:07 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 19:45:39 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_wall(t_data *data, t_mlx *img)
{
	int				ray;
	float			distance;
	t_wall_tex_data	walltex;

	ray = 0;
	load_textures(data, walltex.tex_data.texture);
	while (ray < WIDTH)
	{
		distance = calculate_ray_distance(data, ray);
		fill_wall_data(&walltex.wall_data, distance, data);
		draw_textured_wall(img, ray, &walltex, data);
		draw_ceiling_floor(data, img, ray, &walltex.wall_data);
		ray++;
	}
	free_textures(walltex.tex_data.texture);
}

float	calculate_ray_distance(t_data *data, int ray)
{
	double	ray_angle;

	ray_angle = data->player->angle + (data->player->fov_rd / 2) - (ray
			* data->player->fov_rd / WIDTH);
	return (cast_ray(data, ray_angle));
}

int	calculate_wall_height(float distance, t_data *data)
{
	return ((int)((TILE_SIZE / distance) * (WIDTH / (2
				* tan(data->player->fov_rd / 2)))));
}

void	fill_wall_data(t_wall_data *wall_data, float distance, t_data *data)
{
	wall_data->distance = distance;
	wall_data->wall_height = calculate_wall_height(distance, data);
	wall_data->top_pixel = (HEIGHT / 2) - (wall_data->wall_height / 2);
	wall_data->bottom_pixel = (HEIGHT / 2) + (wall_data->wall_height / 2);
}

void	draw_ceiling_floor(t_data *data, t_mlx *img, int ray,
		t_wall_data *wall_data)
{
	draw_ceiling(img, ray, wall_data->top_pixel, data->colors.ceiling_color);
	draw_floor(img, ray, wall_data->bottom_pixel, data->colors.floor_color);
}
