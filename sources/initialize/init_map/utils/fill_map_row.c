#include "cub3d.h"

void fill_map_row(int *map_row, char *line, int w_map, t_data *data)
{
	int j;

	j = 0;
	while ((line[j] != '\0' && line[j] != '\n') && j < w_map)
	{
		if (line[j] == ' ')
			map_row[j] = FORBIDDEN_SPACE;
		else if (line[j] == '1')
			map_row[j] = WALL;
		else if (line[j] == '0')
			map_row[j] = FREE_SPACE;
		else if (line[j] == 'N')
			map_row[j] = PLAYER_NORTH;
		else if (line[j] == 'S')
			map_row[j] = PLAYER_SOUTH;
		else if (line[j] == 'E')
			map_row[j] = PLAYER_EAST;
		else if (line[j] == 'W')
			map_row[j] = PLAYER_WEST;
		else if (line[j] == ' ')
			map_row[j] = FORBIDDEN_SPACE;
		else
			ft_exit("Map Error", data);
		j++;
	}
	while (j < w_map)
	{
		map_row[j] = FORBIDDEN_SPACE;
		j++;
	}
}
