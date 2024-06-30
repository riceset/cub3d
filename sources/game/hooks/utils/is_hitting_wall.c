/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hitting_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:34:50 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/06/30 17:34:51 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_hitting_wall(float player_center_x, float player_center_y, t_data *data)
{
	int	radius;
	int	map_x;
	int	map_y;

	radius = TILE_SIZE / 7;
	map_x = (int)(player_center_x / TILE_SIZE);
	map_y = (int)((player_center_y - radius) / TILE_SIZE);
	if (data->map[map_y][map_x] == WALL)
		return (1);
	map_y = (int)((player_center_y + radius) / TILE_SIZE);
	if (data->map[map_y][map_x] == WALL)
		return (1);
	map_x = (int)((player_center_x - radius) / TILE_SIZE);
	map_y = (int)(player_center_y / TILE_SIZE);
	if (data->map[map_y][map_x] == WALL)
		return (1);
	map_x = (int)((player_center_x + radius) / TILE_SIZE);
	if (data->map[map_y][map_x] == WALL)
		return (1);
	return (0);
}
