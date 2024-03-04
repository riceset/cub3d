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

int numcout(char *str)
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
	tmp = -1;
	width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		tmp = numcout(line);
		if(tmp > width)
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
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
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

t_data *init_data(char **argv)
{
	char *line;
	int fd;
	t_data *data;

	(void)ft_isdigit(**argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\n");

	data = (t_data *)malloc(sizeof(t_data));
	data->h_map = get_height(argv[1]);
	data->w_map = get_width(argv[1]);
	printf("map_height: %d\n", data->h_map);
	printf("map_width: %d\n", data->w_map);
	if (fd == -1)
		perror("Error opening file");
	close(fd);
	return data;
}
