/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:11:47 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 00:11:42 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_error(char *line, int fd, t_data *data)
{
	free(line);
	close(fd);
	ft_exit("Map Error", data);
}

static int	is_valid_color_format(char **tmp)
{
	return (tmp && tmp[0] && tmp[1] && tmp[2] && !tmp[3]);
}

static int	process_color_line(char *line, int fd, t_data *data)
{
	char	**tmp;
	int		color;

	tmp = ft_split(line, ',');
	if (!is_valid_color_format(tmp))
	{
		free_array(tmp);
		handle_error(line, fd, data);
	}
	color = rgb_to_int(ft_atoi(tmp[0] + 1), ft_atoi(tmp[1]), ft_atoi(tmp[2]));
	free_array(tmp);
	if (color == -1)
		handle_error(line, fd, data);
	return (color);
}

int	get_map_colors(char *filename, t_data *data, char type)
{
	int		color;
	int		fd;
	char	*line;

	color = -1;
	fd = open_file(filename, data);
	if (fd == -1)
		ft_exit("Error opening file", data);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == type && ft_isspace(line[1]))
		{
			if (color != -1 || check_line(line) == ERROR)
			{
				free(line);
				handle_error(NULL, fd, data);
			}
			color = process_color_line(line, fd, data);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (color);
}
