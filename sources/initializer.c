/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:28:54 by hhagiwar              #+#    #+#             */
/*   Updated: 2024/03/04 14:28:55 by hhagiwar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int num_cout(char *str)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		if (ft_isdigit(*str) || *str == '\t' || *str == ' ')
		{
			count++;
			if (count == INT_MAX)
				exit(EXIT_FAILURE);
		}
		str++;
	}
	return count;
}

int get_width(char *filename)
{
	int width;
	int fd;
	char *line;
	int tmp;

	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file");
	tmp = -1;
	width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		tmp = num_cout(line);
		if (tmp > width)
			width = tmp;
		free(line);
	}
	close(fd);
	return width;
}

int get_height(char *filename)
{
	char *line;
	int fd;
	int height;
	int is_map_started = 0;

	fd = open(filename, O_RDONLY, 0);
	if (fd == -1)
		ft_exit("Error opening file");
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		char *temp = line;
		while (*temp == ' ' || *temp == '\t')
			temp++;
		if (*temp != '\0' && (is_map_started || (*temp >= '0' && *temp <= '9')))
		{
			is_map_started = 1;
			height++;
		}
		free(line);
	}
	close(fd);
	return height;
}

int **allocate_map_memory(int h_map, int w_map)
{
	int i = 0;
	int **map;
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
	return map;
}

int open_file(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_exit("Error opening file");
	return fd;
}

void fill_map_row(int *map_row, char *line, int w_map)
{
	int j = 0;
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
		else
			map_row[j] = FORBIDDEN_SPACE;
		j++;
	}
	while (j < w_map)
	{
		map_row[j] = FORBIDDEN_SPACE;
		j++;
	}
}

int **init_map(char *filename, int h_map, int w_map)
{
	int fd;
	int **map;
	char *line;
	int i = 0;

	map = allocate_map_memory(h_map, w_map);
	fd = open_file(filename);

	while ((line = get_next_line(fd)) != NULL && i < h_map)
	{
		char *temp = ft_strdup(line);
		while (*temp == ' ' || *temp == '\t')
			temp++;
		if ((line[0] != '\0' || line[0] != '\n') && (*temp >= '0' && *temp <= '9'))
		{
			fill_map_row(map[i], line, w_map);
			i++;
		}
		free(line);
	}
	close(fd);
	return map;
}

int extension_check(char *filename)
{
	int i;

	i = 0;
	while (filename[i] != '\0' && filename[i] != '.')
		i++;
	if ( i != 0 && filename[i] == '.' && filename[i + 1] == 'c' && filename[i + 2] == 'u' && filename[i + 3] == 'b' && filename[i + 4] == '\0')
		return SUCCESS;
	return ERROR;
}

t_data *init_data(char **argv)
{
	t_data *data;

	if (extension_check(argv[1]) == ERROR)
        ft_exit("File extension must be .cub");
	print_file(argv[1]);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit("Memory allocation failed");
	data->h_map = get_height(argv[1]);
	data->w_map = get_width(argv[1]);
	if (data->h_map < 1 || data->w_map < 1)
		ft_exit("Map Error");
	data->map = init_map(argv[1], data->h_map, data->w_map);
	print_map(data->map, data->w_map);
	return data;
}
