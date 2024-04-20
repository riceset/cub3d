#include "cub3d.h"

int get_map_height(char *filename, t_data *data)
{
	char *line;
	int fd;
	int height;
	int is_map_started;
	char *temp;

	is_map_started = 0;
	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file", data);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		temp = line;
		while (ft_isspace(*temp))
			temp++;
		if ((*temp != '\0' || *temp != '\n') && (is_map_started || (*temp >= '0' && *temp <= '9')))
		{
			is_map_started = 1;
			height++;
		}
		free(line);
	}
	close(fd);
    printf("height:%d\n", height);
	return (height);
}
