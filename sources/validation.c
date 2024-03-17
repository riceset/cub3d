#include "cub3d.h"

void flood_fill(int **map, int x, int y, int h_map, int w_map, int *status);
int **copy_map(int **src, int h_map, int w_map);

int validate_map(t_data *data)
{
	int status = 0;
	int **map_copy = copy_map(data->map, data->h_map, data->w_map);
	if (!map_copy)
	{
		ft_exit("Failed to copy map for validation", data);
	}
	flood_fill(map_copy, data->player->plyr_x, data->player->plyr_y, data->h_map, data->w_map, &status);
	int i = 0;
	while (i < data->h_map)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	return status;
}

void flood_fill(int **map, int x, int y, int h_map, int w_map, int *status)
{
	x /= TILE_SIZE;
	y /= TILE_SIZE;
	if (x < 0 || x >= w_map || y < 0 || y >= h_map || map[y][x] == FORBIDDEN_SPACE)
	{
		*status = 1;
		return;
	}
	if (map[y][x] == -1 || map[y][x] == WALL)
	{
		return;
	}

	map[y][x] = -1;

	flood_fill(map, x + 1, y, h_map, w_map, status);
	flood_fill(map, x - 1, y, h_map, w_map, status);
	flood_fill(map, x, y + 1, h_map, w_map, status);
	flood_fill(map, x, y - 1, h_map, w_map, status);
}


int **copy_map(int **src, int h_map, int w_map)
{
	int **copy = (int **)malloc(sizeof(int *) * h_map);
	if (!copy)
	{
		return NULL;
	}

	int i = 0;
	while (i < h_map)
	{
		copy[i] = (int *)malloc(sizeof(int) * w_map);
		if (!copy[i])
		{
			while (i > 0)
			{
				i--;
				free(copy[i]);
			}
			free(copy);
			return NULL;
		}

		int j = 0;
		while (j < w_map)
		{
			copy[i][j] = src[i][j];
			j++;
		}
		i++;
	}
	return copy;
}
