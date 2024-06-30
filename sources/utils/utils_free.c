/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:15:03 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/06/30 17:25:37 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(int **map, int height)
{
	int	i;

	i = 0;
	if (map)
	{
		while (i < height)
		{
			if (map[i])
				free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->map)
			free_map(data->map, data->h_map);
		while (i < 4)
		{
			if (data->texture[i])
				free(data->texture[i]);
			i++;
		}
		if (data->player)
			free(data->player);
		free(data);
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}
