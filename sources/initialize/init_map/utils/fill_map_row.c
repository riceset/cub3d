/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_row.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:57:28 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/02 23:57:52 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map_char(int *map_row, char c, int index, t_data *data)
{
	if (c == ' ')
		map_row[index] = FORBIDDEN_SPACE;
	else if (c == '1')
		map_row[index] = WALL;
	else if (c == '0')
		map_row[index] = FREE_SPACE;
	else if (c == 'N')
		map_row[index] = PLAYER_NORTH;
	else if (c == 'S')
		map_row[index] = PLAYER_SOUTH;
	else if (c == 'E')
		map_row[index] = PLAYER_EAST;
	else if (c == 'W')
		map_row[index] = PLAYER_WEST;
	else
		ft_exit("Map Error", data);
}

void	fill_remaining_spaces(int *map_row, int start_index, int w_map)
{
	while (start_index < w_map)
	{
		map_row[start_index] = FORBIDDEN_SPACE;
		start_index++;
	}
}

void	fill_map_row(int *map_row, char *line, t_data *data)
{
	int	j;

	j = 0;
	while ((line[j] != '\0' && line[j] != '\n') && j < data->w_map)
	{
		process_map_char(map_row, line[j], j, data);
		j++;
	}
	fill_remaining_spaces(map_row, j, data->w_map);
}
