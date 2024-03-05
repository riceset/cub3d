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

void ft_exit(char *err_msg)
{
	perror(err_msg);
	exit(EXIT_FAILURE);
}

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

char **allocate_map_memory(int h_map, int w_map)
{
	int i = 0;
	char **map;
	map = (char **)malloc(sizeof(char *) * h_map);
	if (!map)
		ft_exit("Memory allocation failed");
	while (i < h_map)
	{
		map[i] = (char *)malloc(sizeof(char) * (w_map + 1));
		if (!map[i])
			ft_exit("Memory allocation failed");
		i++;
	}
	return map;
}

char **init_map(char *filename, int h_map, int w_map)
{
	int fd;
	char **map;
	char *line;
	int i = 0;
	int is_map_started = 0;

	map = allocate_map_memory(h_map, w_map);
	i = 0;
	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_exit("Error opening file");
	while ((line = get_next_line(fd)) != NULL && i < h_map)
	{
		int j = 0;
		char *temp = ft_strdup(line);
		while (*temp == ' ' || *temp == '\t')
			temp++;
		if ((line[j] != '\0' || line[j] != '\n') && (is_map_started || (*temp >= '0' && *temp <= '9')))
		{
			is_map_started = 1;
			while ((line[j] != '\0' && line[j] != '\n') && j < w_map)
			{
				map[i][j] = line[j];
				j++;
			}
			while (j < w_map)
			{
				map[i][j] = ' ';
				j++;
			}
			map[i][j] = '\0';
			i++;
		}
		free(line);
	}
	map[i] = NULL;
	i = 0;
	close(fd);
	return map;
}

void print_file(char *filename)
{
    char *line;
    int fd;
    int line_number = 1;
    printf("--------- Start of %s ---------\n", filename);
    fd = open(filename, O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%d: %s", line_number, line);
        free(line);
        line_number++;
    }
    printf("\n--------- End of %s ---------\n\n", filename);
    close(fd);
}


void print_map(char **map)
{
    int i = 0;
    printf("--------- Start of Map ---------\n");
    while(map[i] != NULL)
    {
        printf("%s\n", map[i]);
        i++;
    }
    printf("--------- End of Map ---------\n\n");
}


t_data *init_data(char **argv)
{
	t_data *data;

	print_file(argv[1]);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		ft_exit("Memory allocation failed");
	data->h_map = get_height(argv[1]);
	data->w_map = get_width(argv[1]);
	if(data->h_map < 1 || data->w_map < 1)
		ft_exit("Map Error");
	data->map = init_map(argv[1], data->h_map, data->w_map);
	print_map(data->map);
	return data;
}
