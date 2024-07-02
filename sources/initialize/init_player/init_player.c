/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:56:23 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/02 11:06:46 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		find_player_position(t_player *player, t_data *data);

t_player	*init_player(t_data *data)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		ft_exit("Memory allocation failed", data);
	player->plyr_x = -1;
	player->plyr_y = -1;
	player->fov_rd = M_PI / 3;
	find_player_position(player, data);
	if (player->plyr_x == -1 || player->plyr_y == -1)
		ft_exit("not found player", data);
	else
		player->angle = init_angle(player);
	return (player);
}

void	find_player_position(t_player *player, t_data *data)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (i < data->h_map)
	{
		while (j < data->w_map)
		{
			if (is_direction_map(data->map[i][j]) == TRUE)
			{
				player_count++;
				if (player_count == 2)
					ft_exit("Multiple player detected", data);
				player->plyr_x = j * TILE_SIZE;
				player->plyr_y = i * TILE_SIZE;
				player->player_status = data->map[i][j];
			}
			j++;
		}
		j = 0;
		i++;
	}
}
