/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiro <hiro@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:30:57 by tkomeno           #+#    #+#             */
/*   Updated: 2024/03/06 13:48:18 by hiro             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	num_cout(char *str)
{
	int	count;

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

int	get_width(char *filename)
{
	int		width;
	int		fd;
	char	*line;
	int		tmp;

	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file");
	tmp = -1;
	width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp = num_cout(line);
		if (tmp > width)
			width = tmp;
		free(line);
	}
	close(fd);
	return (width);
}

int	get_height(char *filename)
{
	char	*line;
	int		fd;
	int		height;
	int		is_map_started;
	char	*temp;

	is_map_started = 0;
	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file");
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		temp = line;
		while (ft_isspace(*temp))
			temp++;
		if (*temp != '\0' && (is_map_started || (*temp >= '0' && *temp <= '9')))
		{
			is_map_started = 1;
			height++;
		}
		free(line);
	}
	close(fd);
	return (height);
}

int	**allocate_map_memory(int h_map, int w_map)
{
	int	i;
	int	**map;

	i = 0;
	map = (int **)malloc(sizeof(int *) * h_map);
	if (!map)
		ft_exit("Memory allocation failed");
	while (i < h_map)
	{
		map[i] = (int *)malloc(sizeof(int) * (w_map + 1));
		if (!map[i])
			ft_exit("Memory allocation failed");
		i++;
	}
	return (map);
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_exit("Error opening file");
	return (fd);
}

void	fill_map_row(int *map_row, char *line, int w_map)
{
	int	j;

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
			ft_exit("Map Error");
		j++;
	}
	while (j < w_map)
	{
		map_row[j] = FORBIDDEN_SPACE;
		j++;
	}
}

int	**init_map(char *filename, int h_map, int w_map)
{
	int		fd;
	int		**map;
	char	*line;
	int		i;
	char	*temp;

	i = 0;
	map = allocate_map_memory(h_map, w_map);
	fd = open_file(filename);
	while ((line = get_next_line(fd)) != NULL && i < h_map)
	{
		temp = ft_strdup(line);
		while (ft_isspace(*temp))
			temp++;
		if ((line[0] != '\0' || line[0] != '\n') && (*temp >= '0'
				&& *temp <= '9'))
		{
			fill_map_row(map[i], line, w_map);
			i++;
		}
		free(line);
	}
	close(fd);
	return (map);
}

t_player *init_player(t_data *data)
{
	t_player *player;
	int i=0;
	int j=0;
	int player_count = 0;

	player = (t_player *)malloc(sizeof(t_player));
	if(!player)
		ft_exit("Memory allocation failed");
	player->plyr_x = -1;
	player->plyr_y = -1;
	while(i < data->h_map)
	{
		while(j < data->w_map)
		{
			if(data->map[i][j] == PLAYER_EAST || data->map[i][j] == PLAYER_WEST || data->map[i][j] == PLAYER_SOUTH || data->map[i][j] == PLAYER_NORTH)
			{
				player_count++;
				if(player_count == 2)
					ft_exit("Multiple player detected");
				player->plyr_x = j;
				player->plyr_y = i;
				player->player_status = data->map[i][j];
			}
			j++;
		}
		j = 0;
		i++;
	}
	if(player->plyr_x == -1 || player->plyr_y == -1)
		ft_exit("not found player");
	return player;
}

void flood_fill(int **map, int x, int y, int h_map, int w_map, int *status) {
    if (x < 0 || x >= w_map || y < 0 || y >= h_map || map[y][x] == FORBIDDEN_SPACE) {
        *status = 1;
        return;
    }
    if (map[y][x] == -1 || map[y][x] == WALL) {
        return;
    }

    map[y][x] = -1;

    flood_fill(map, x + 1, y, h_map, w_map, status);
    flood_fill(map, x - 1, y, h_map, w_map, status);
    flood_fill(map, x, y + 1, h_map, w_map, status);
    flood_fill(map, x, y - 1, h_map, w_map, status);
}

int validate_map(t_data *data) {
    int status = 0;

    flood_fill(data->map, data->player->plyr_x, data->player->plyr_y, data->h_map, data->w_map, &status);
    return status;
}


t_data	*init_data(char **argv)
{
	t_data	*data;

	print_file(argv[1]);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit("Memory allocation failed");
	data->h_map = get_height(argv[1]);
	data->w_map = get_width(argv[1]);
	if (data->h_map < 9 || data->w_map < 7)
		ft_exit("Map Error");
	data->map = init_map(argv[1], data->h_map, data->w_map);
	print_map(data->map, data->w_map);
	data->player = init_player(data);
	printf("flood_fill:%d\n", validate_map(data));
	return (data);
}
