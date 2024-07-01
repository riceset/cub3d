#include "cub3d.h"

void	flood_fill(int **map, int x, int y, int h_map, int w_map, int *status)
{
	if (x < 0 || x >= w_map || y < 0 || y >= h_map
		|| map[y][x] == FORBIDDEN_SPACE)
	{
		*status = 1;
		return ;
	}
	if (map[y][x] == -1 || map[y][x] == WALL)
	{
		return ;
	}
	map[y][x] = -1;
	flood_fill(map, x + 1, y, h_map, w_map, status);
	flood_fill(map, x - 1, y, h_map, w_map, status);
	flood_fill(map, x, y + 1, h_map, w_map, status);
	flood_fill(map, x, y - 1, h_map, w_map, status);
}
