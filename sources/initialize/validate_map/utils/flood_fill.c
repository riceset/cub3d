/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:41:27 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 15:20:17 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(int **map, t_int_point point, t_data *data, int *status)
{
	t_int_point	new_point;

	if (point.x < 0 || point.x >= data->w_map || point.y < 0
		|| point.y >= data->h_map || map[point.y][point.x] == FORBIDDEN_SPACE)
	{
		*status = 1;
		return ;
	}
	if (map[point.y][point.x] == -1 || map[point.y][point.x] == WALL)
	{
		return ;
	}
	map[point.y][point.x] = -1;
	new_point = (t_int_point){point.x + 1, point.y};
	flood_fill(map, new_point, data, status);
	new_point = (t_int_point){point.x - 1, point.y};
	flood_fill(map, new_point, data, status);
	new_point = (t_int_point){point.x, point.y + 1};
	flood_fill(map, new_point, data, status);
	new_point = (t_int_point){point.x, point.y - 1};
	flood_fill(map, new_point, data, status);
}
