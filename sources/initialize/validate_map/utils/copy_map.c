/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@tokyo.42.school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:34:10 by hhagiwar          #+#    #+#             */
/*   Updated: 2024/07/03 15:20:37 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_copy(int **copy, int i)
{
	while (i > 0)
	{
		i--;
		free(copy[i]);
	}
	free(copy);
}

int	**allocate_map_copy(int h_map, int w_map)
{
	int	**copy;
	int	i;

	copy = (int **)malloc(sizeof(int *) * h_map);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < h_map)
	{
		copy[i] = (int *)malloc(sizeof(int) * w_map);
		if (!copy[i])
		{
			free_map_copy(copy, i);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

void	copy_map_data(int **src, int **copy, int h_map, int w_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < h_map)
	{
		j = 0;
		while (j < w_map)
		{
			copy[i][j] = src[i][j];
			j++;
		}
		i++;
	}
}

int	**copy_map(int **src, int h_map, int w_map)
{
	int	**copy;

	copy = allocate_map_copy(h_map, w_map);
	if (!copy)
		return (NULL);
	copy_map_data(src, copy, h_map, w_map);
	return (copy);
}
