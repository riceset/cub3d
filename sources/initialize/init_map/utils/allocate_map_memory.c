#include "cub3d.h"

int **allocate_map_memory(int h_map, int w_map, t_data *data)
{
	int i;
	int **map;

	i = 0;
	map = (int **)malloc(sizeof(int *) * h_map);
	if (!map)
		ft_exit("Memory allocation failed", data);
	while (i < h_map)
	{
		map[i] = (int *)malloc(sizeof(int) * (w_map + 1));
		if (!map[i])
			ft_exit("Memory allocation failed", data);
		i++;
	}
	return (map);
}

