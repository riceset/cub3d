/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:07:15 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 15:19:05 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(t_data *data)
{
	int			status;
	t_int_point	player_pos;
	int			**map_copy;
	int			i;

	status = 0;
	player_pos.x = data->player->plyr_x / TILE_SIZE;
	player_pos.y = data->player->plyr_y / TILE_SIZE;
	map_copy = copy_map(data->map, data->h_map, data->w_map);
	if (!map_copy)
		ft_exit("Failed to copy map for validation", data);
	flood_fill(map_copy, player_pos, data, &status);
	i = 0;
	while (i < data->h_map)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (status);
}
