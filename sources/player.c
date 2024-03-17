#include "cub3d.h"

double init_angle(t_player *player);

t_player *init_player(t_data *data)
{
	t_player *player;
	int i = 0;
	int j = 0;
	int player_count = 0;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		ft_exit("Memory allocation failed", data);
	player->plyr_x = -1;
	player->plyr_y = -1;
	player->fov_rd = M_PI / 3;
	while (i < data->h_map)
	{
		while (j < data->w_map)
		{
			if (data->map[i][j] == PLAYER_EAST || data->map[i][j] == PLAYER_WEST || data->map[i][j] == PLAYER_SOUTH || data->map[i][j] == PLAYER_NORTH)
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
	if (player->plyr_x == -1 || player->plyr_y == -1)
		ft_exit("not found player", data);
	else
		player->angle = init_angle(player);
	return player;
}

double init_angle(t_player *player)
{
	if(player->player_status == PLAYER_EAST)
		return 0;
	else if(player->player_status == PLAYER_NORTH)
		return M_PI * 1 / 2;
	else if(player->player_status == PLAYER_WEST)
		return M_PI;
	else
		return M_PI * 3 / 2;
}
