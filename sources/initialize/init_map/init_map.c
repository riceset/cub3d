/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:00:13 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/06/30 18:33:02 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_line(char *line, int **map, int row_index, int w_map, t_data *data)
{
	char	*temp;

	temp = line;
	while (*temp && ft_isspace(*temp))
		temp++;
	if (*temp == '\0' || *temp == '\n')
		return (0);
	if (ft_isdigit(*temp))
	{
		fill_map_row(map[row_index], line, w_map, data);
		return (1);
	}
	return (0);
}

int	**init_map(char *filename, int h_map, int w_map, t_data *data)
{
	int		fd;
	int		**map;
	char	*line;
	int		i;

	i = 0;
	map = allocate_map_memory(h_map, w_map, data);
	fd = open_file(filename, data);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (process_line(line, map, i, w_map, data))
			i++;
		free(line);
	}
    while ((line = get_next_line(fd)) != NULL)
        free(line);
	close(fd);
	return (map);
}
