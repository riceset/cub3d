/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_direction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:52:34 by riceset           #+#    #+#             */
/*   Updated: 2024/07/04 19:52:44 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_east(t_data *data, double distance, double ray_angle,
		t_texture_data *tex_data)
{
	tex_data->hitY = data->player->plyr_y - distance * sin(ray_angle);
	tex_data->wallX = fmod(tex_data->hitY, TILE_SIZE);
	tex_data->texX = -(int)((TILE_SIZE / 2 + tex_data->wallX)
			* tex_data->texture[EAST]->width / TILE_SIZE)
		% tex_data->texture[EAST]->width;
}

void	handle_west(t_data *data, double distance, double ray_angle,
		t_texture_data *tex_data)
{
	tex_data->hitY = data->player->plyr_y - distance * sin(ray_angle);
	tex_data->wallX = fmod(tex_data->hitY, TILE_SIZE);
	tex_data->texX = (int)((TILE_SIZE / 2 + tex_data->wallX)
			* tex_data->texture[WEST]->width / TILE_SIZE)
		% tex_data->texture[WEST]->width;
}

void	handle_south(t_data *data, double distance, double ray_angle,
		t_texture_data *tex_data)
{
	tex_data->hitX = data->player->plyr_x + distance * cos(ray_angle);
	tex_data->wallX = fmod(tex_data->hitX, TILE_SIZE);
	tex_data->texX = (int)((TILE_SIZE / 2 + tex_data->wallX)
			* tex_data->texture[SOUTH]->width / TILE_SIZE)
		% tex_data->texture[SOUTH]->width;
}

void	handle_north(t_data *data, double distance, double ray_angle,
		t_texture_data *tex_data)
{
	tex_data->hitX = data->player->plyr_x + distance * cos(ray_angle);
	tex_data->wallX = fmod(tex_data->hitX, TILE_SIZE);
	tex_data->texX = -(int)((TILE_SIZE / 2 + tex_data->wallX)
			* tex_data->texture[NORTH]->width / TILE_SIZE)
		% tex_data->texture[NORTH]->width;
}
