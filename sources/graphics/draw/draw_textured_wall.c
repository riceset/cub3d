/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:59:28 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 19:53:32 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_textured_wall(t_mlx *img, int ray, t_wall_tex_data *walltex,
		t_data *data)
{
	int	direction;

	direction = get_direction(data, ray, &walltex->tex_data);
	draw_textured_pixels(img, ray, direction, walltex);
}

void	calculate_hits_and_texture(t_data *data, double ray_angle,
		int direction, t_texture_data *tex_data)
{
	double	distance;

	distance = cast_ray(data, ray_angle);
	if (direction == EAST)
	{
		handle_east(data, distance, ray_angle, tex_data);
	}
	else if (direction == WEST)
	{
		handle_west(data, distance, ray_angle, tex_data);
	}
	else if (direction == SOUTH)
	{
		handle_south(data, distance, ray_angle, tex_data);
	}
	else if (direction == NORTH)
	{
		handle_north(data, distance, ray_angle, tex_data);
	}
}

int	get_direction(t_data *data, int ray, t_texture_data *tex_data)
{
	double	ray_angle;
	int		direction;

	ray_angle = data->player->angle + (data->player->fov_rd / 2) - (ray
			* data->player->fov_rd / WIDTH);
	direction = determine_wall_direction(data, ray_angle);
	calculate_hits_and_texture(data, ray_angle, direction, tex_data);
	return (direction);
}

void	draw_textured_pixels(t_mlx *img, int ray, int direction,
		t_wall_tex_data *wt)
{
	int	pixel_y;
	int	tex_y;
	int	color;
	int	draw_start;
	int	draw_end;

	draw_start = wt->wall_data.top_pixel;
	draw_end = wt->wall_data.bottom_pixel;
	pixel_y = draw_start - 1;
	while (++pixel_y < draw_end)
	{
		if (pixel_y >= 0 && pixel_y < HEIGHT)
		{
			tex_y = ((pixel_y - wt->wall_data.top_pixel)
					* wt->tex_data.texture[direction]->height)
				/ wt->wall_data.wall_height;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= wt->tex_data.texture[direction]->height)
				tex_y = wt->tex_data.texture[direction]->height - 1;
			color = get_texture_color(wt->tex_data.texture[direction],
					wt->tex_data.texX, tex_y);
			my_mlx_pixel_put(img, ray, pixel_y, color);
		}
	}
}
