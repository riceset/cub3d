#include "cub3d.h"

int	validate_map(t_data *data)
{
	int	status;
	int	player_x;
	int	player_y;
	int	**map_copy;
	int	i;

	status = 0;
	player_x = data->player->plyr_x / TILE_SIZE;
	player_y = data->player->plyr_y / TILE_SIZE;
	map_copy = copy_map(data->map, data->h_map, data->w_map);
	if (!map_copy)
		ft_exit("Failed to copy map for validation", data);
	flood_fill(map_copy, player_x, player_y, data->h_map, data->w_map, &status);
	i = 0;
	while (i < data->h_map)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return (status);
}
