#include "cub3d.h"

int **init_map(char *filename, int h_map, int w_map, t_data *data)
{
	int fd;
	int **map;
	char *line;
	int i;
	char *temp;

	i = 0;
	map = allocate_map_memory(h_map, w_map, data);
	fd = open_file(filename, data);
	while ((line = get_next_line(fd)) != NULL && i < h_map)
	{
		temp = ft_strdup(line);
		while (*temp && ft_isspace(*temp))
			temp++;
		if (*temp == '\0' || *temp == '\n')
		{
			free(line);
			continue;
		}
		if ((*temp != '\0' && *temp != '\n') && ft_isdigit(*temp))
		{
			fill_map_row(map[i], line, w_map, data);
			i++;
		}
		free(temp);
		free(line);
	}
	close(fd);
	return (map);
}
