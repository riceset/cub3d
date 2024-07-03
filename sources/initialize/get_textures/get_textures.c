/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:26:51 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 14:32:57 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0);
}

static void	process_texture_line(char *line, t_data *data, int *texture_index)
{
	char	*path;

	if (is_texture_line(line))
	{
		path = ft_strtrim(line + 3, " \t\n");
		if (path == NULL)
			ft_exit("Failed to allocate memory for texture path", data);
		data->texture[*texture_index] = path;
		(*texture_index)++;
	}
}

static void	read_texture_file(int fd, t_data *data)
{
	char	*line;
	int		texture_index;

	texture_index = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_texture_line(line, data, &texture_index);
		free(line);
		line = get_next_line(fd);
	}
}

char	**get_textures(char *filename, t_data **data)
{
	int	fd;

	fd = open_file(filename, *data);
	read_texture_file(fd, *data);
	close(fd);
	return (NULL);
}
