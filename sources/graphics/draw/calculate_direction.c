/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_direction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:52:34 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 19:57:14 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_east(t_data *data, double distance, double ray_angle,
		t_texture_data *tex_data)
{
	tex_data->hit_y = data->player->plyr_y - distance * sin(ray_angle);
	tex_data->wall_x = fmod(tex_data->hit_y, TILE_SIZE);
	tex_data->tex_x = -(int)((TILE_SIZE / 2 + tex_data->wall_x)
			* tex_data->texture[EAST]->width / TILE_SIZE)
		% tex_data->texture[EAST]->width;
}

void	handle_west(t_data *data, double distance, double ray_angle,
		t_texture_data *tex_data)
{
	tex_data->hit_y = data->player->plyr_y - distance * sin(ray_angle);
	tex_data->wall_x = fmod(tex_data->hit_y, TILE_SIZE);
	tex_data->tex_x = (int)((TILE_SIZE / 2 + tex_data->wall_x)
			* tex_data->texture[WEST]->width / TILE_SIZE)
		% tex_data->texture[WEST]->width;
}

void	handle_south(t_data *data, double distance, double ray_angle,
		t_texture_data *tex_data)
{
	tex_data->hit_x = data->player->plyr_x + distance * cos(ray_angle);
	tex_data->wall_x = fmod(tex_data->hit_x, TILE_SIZE);
	tex_data->tex_x = (int)((TILE_SIZE / 2 + tex_data->wall_x)
			* tex_data->texture[SOUTH]->width / TILE_SIZE)
		% tex_data->texture[SOUTH]->width;
}

void	handle_north(t_data *data, double distance, double ray_angle,
		t_texture_data *tex_data)
{
	tex_data->hit_x = data->player->plyr_x + distance * cos(ray_angle);
	tex_data->wall_x = fmod(tex_data->hit_x, TILE_SIZE);
	tex_data->tex_x = -(int)((TILE_SIZE / 2 + tex_data->wall_x)
			* tex_data->texture[NORTH]->width / TILE_SIZE)
		% tex_data->texture[NORTH]->width;
}
