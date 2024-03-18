#include "cub3d.h"

int **allocate_map_memory(int h_map, int w_map, t_data *data);
int open_file(char *filename);

int get_width(char *filename, t_data *data)
{
	int width;
	int fd;
	char *line;
	int tmp;

	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file", data);
	tmp = -1;
	width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		tmp = num_count(line);
		if (tmp > width && (ft_isdigit(line[0]) || ft_isspace(line[0])))
			width = tmp;
		free(line);
	}
	close(fd);
    return (width - 1);
}

int num_count(char *str)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		if (ft_isdigit(*str) || ft_isspace(*str))
		{
			count++;
			if (count == INT_MAX)
				exit(EXIT_FAILURE);
		}
		str++;
	}
	return (count);
}

int get_height(char *filename, t_data *data)
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

int **init_map(char *filename, int h_map, int w_map, t_data *data)
{
	int fd;
	int **map;
	char *line;
	int i;
	char *temp;

	i = 0;
	map = allocate_map_memory(h_map, w_map, data);
	fd = open_file(filename);
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
		if ((*temp != '\0' && *temp != '\n') && (*temp >= '0' && *temp <= '9'))
		{
			fill_map_row(map[i], line, w_map, data);
			i++;
		}
		free(line);
	}
	close(fd);
	return (map);
}


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
