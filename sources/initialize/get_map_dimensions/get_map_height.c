/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_height.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:17:47 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 14:26:10 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(char *line, int *is_map_started)
{
	char	*temp;

	temp = line;
	while (*temp && ft_isspace(*temp))
		temp++;
	if ((*temp != '\0' && *temp != '\n') && (*is_map_started || (*temp >= '0'
				&& *temp <= '9')))
	{
		*is_map_started = 1;
		return (1);
	}
	return (0);
}

static int	process_line(char *line, int *is_map_started)
{
	if (is_map_line(line, is_map_started))
		return (1);
	return (0);
}

static int	calculate_map_height(int fd, t_data *data)
{
	char	*line;
	int		height;
	int		is_map_started;

	height = 0;
	is_map_started = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_line(line, &is_map_started))
			height++;
		free(line);
		line = get_next_line(fd);
	}
	if (height > 50)
		ft_exit("Map height must be <= 50", data);
	return (height);
}

int	get_map_height(char *filename, t_data *data)
{
	int	fd;
	int	height;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_exit("Error opening file", data);
	height = calculate_map_height(fd, data);
	close(fd);
	return (height);
}
