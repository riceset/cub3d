/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map_memory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 00:01:33 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 00:01:46 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	**allocate_map_memory(t_data *data)
{
	int	i;
	int	**map;

	i = 0;
	map = (int **)malloc(sizeof(int *) * data->h_map);
	if (!map)
		ft_exit("Memory allocation failed", data);
	while (i < data->h_map)
	{
		map[i] = (int *)malloc(sizeof(int) * (data->w_map + 1));
		if (!map[i])
			ft_exit("Memory allocation failed", data);
		i++;
	}
	return (map);
}
