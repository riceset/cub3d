/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:00:13 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 00:02:50 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_line(char *line, int **map, int row_index, t_data *data)
{
	char	*temp;

	temp = line;
	while (*temp && ft_isspace(*temp))
		temp++;
	if (*temp == '\0' || *temp == '\n')
		return (0);
	if (ft_isdigit(*temp))
	{
		fill_map_row(map[row_index], line, data);
		return (1);
	}
	return (0);
}

int	**init_map(char *filename, t_data *data)
{
	int		fd;
	int		**map;
	char	*line;
	int		i;

	i = 0;
	map = allocate_map_memory(data);
	fd = open_file(filename, data);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_line(line, map, i, data))
			i++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}
