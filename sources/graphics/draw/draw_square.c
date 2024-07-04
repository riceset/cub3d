/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riceset <tkomeno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:54:28 by riceset           #+#    #+#             */
/*   Updated: 2024/07/02 16:56:34 by riceset          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_mlx *img, t_int_point start, int color, int size)
{
	t_int_point	end;
	int			i;
	int			j;

	end.x = (start.x * size) + size;
	end.y = (start.y * size) + size;
	i = start.y * size;
	while (i < end.y)
	{
		j = start.x * size;
		while (j < end.x)
		{
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}
